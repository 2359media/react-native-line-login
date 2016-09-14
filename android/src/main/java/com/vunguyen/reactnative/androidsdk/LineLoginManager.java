package com.vunguyen.reactnative.androidsdk;

import android.util.Log;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableMap;

import jp.line.android.sdk.LineSdkContext;
import jp.line.android.sdk.LineSdkContextManager;
import jp.line.android.sdk.api.ApiClient;
import jp.line.android.sdk.api.ApiRequestFuture;
import jp.line.android.sdk.api.ApiRequestFutureListener;
import jp.line.android.sdk.login.LineAuthManager;
import jp.line.android.sdk.login.LineLoginFuture;
import jp.line.android.sdk.login.LineLoginFutureListener;
import jp.line.android.sdk.model.AccessToken;
import jp.line.android.sdk.model.Profile;

/**
 * Created by vunguyen on 9/13/16.
 */
public class LineLoginManager extends ReactContextBaseJavaModule {
    public LineLoginManager(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    public String getName() {
        return "RNLineLoginManager";
    }

    @ReactMethod
    public void login(final Promise promise) {
        LineSdkContext sdkContext = LineSdkContextManager.getSdkContext();
        LineAuthManager authManager = sdkContext.getAuthManager();

        LineLoginFuture loginFuture = authManager.login(this.getCurrentActivity());
        loginFuture.addFutureListener(new LineLoginFutureListener() {
            @Override
            public void loginComplete(LineLoginFuture future) {

                switch(future.getProgress()) {
                    case SUCCESS:
                        AccessToken accessToken = future.getAccessToken();
                        WritableMap result = Arguments.createMap();
                        result.putString("accessToken", accessToken.accessToken);
                        result.putString("refreshToken", accessToken.refreshToken);
                        result.putString("mid", accessToken.mid);
                        result.putString("expire", accessToken.expire + "");

                        promise.resolve(result);
                        break;
                    case CANCELED: // Login canceled by user
                        promise.reject("401", "Login canceled by user");
                        break;
                    default: // Error
                        promise.reject("401", "Login failed");
                        break;
                }
            }
        });
    }

    @ReactMethod
    public void getUserProfile(final Promise promise) {
        LineSdkContext sdkContext = LineSdkContextManager.getSdkContext();
        ApiClient apiClient = sdkContext.getApiClient();
        apiClient.getMyProfile(new ApiRequestFutureListener() {
            @Override
            public void requestComplete(ApiRequestFuture future) {
                switch(future.getStatus()) {
                    case SUCCESS:
                        Profile profile = (Profile) future.getResponseObject();
                        WritableMap result = Arguments.createMap();
                        result.putString("displayName", profile.displayName);
                        result.putString("mid", profile.mid);
                        result.putString("pictureUrl", profile.pictureUrl);

                        promise.resolve(result);
                        break;
                    default:
                        promise.reject("400", "Failed to get profile");
                        break;
                }
            }
        });
    }

    @ReactMethod
    public void logout() {
        LineSdkContext sdkContext = LineSdkContextManager.getSdkContext();
        LineAuthManager authManager = sdkContext.getAuthManager();

        authManager.logout();
    }
}
