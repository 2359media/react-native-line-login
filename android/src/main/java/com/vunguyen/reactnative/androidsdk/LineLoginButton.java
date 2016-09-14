package com.vunguyen.reactnative.androidsdk;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;

/**
 * Created by vunguyen on 9/13/16.
 */
public class LineLoginButton extends ReactContextBaseJavaModule {
    public static final String REACT_CLASS = "RCTLineLoginButton";

    public LineLoginButton(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    public String getName() {
        return REACT_CLASS;
    }
}
