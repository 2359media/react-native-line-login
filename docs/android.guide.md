# Android Guide
Includes LINE Android SDK v3.1.19

## LINE Getting Started Guide
- [https://developers.line.me/android/development-with-sdk](https://developers.line.me/android/development-with-sdk)


## Setup
- In `android/setting.gradle`

```gradle
...
include ':react-native-line-login', ':app'
project(':react-native-line-login').projectDir = new File(rootProject.projectDir, '../../android')

```

- In `android/app/build.gradle`

```gradle
...
dependencies {
    compile fileTree(dir: "libs", include: ["*.jar"])
    compile "com.android.support:appcompat-v7:23.0.1"
    compile "com.facebook.react:react-native:+"  // From node_modules
    compile project(":react-native-line-login") // <--- add this
}
```

- Register Module (in MainActivity.java)

```java
import com.vunguyen.reactnative.androidsdk.LineReactPackage; // <---- ADD THIS
import jp.line.android.sdk.LineSdkContextManager; // <---- ADD THIS

public class MainApplication extends Application implements ReactApplication {

   /**
   * A list of packages used by the app. If the app uses additional views
   * or modules besides the default ones, add more packages here.
   */
    @Override
    protected List<ReactPackage> getPackages() {
      return Arrays.<ReactPackage>asList(
        new MainReactPackage(),
        new LineReactPackage() // <------ ADD THIS
      );
    }

    @Override
    public void onCreate() {
      super.onCreate();

      // Initialize LINE SDK
      LineSdkContextManager.initialize(this);
    }
```

- Update LINE config (in AndroidManifest.xml)

```xml
<application
    android:name=".MainApplication"
    android:allowBackup="true"
    android:label="@string/app_name"
    android:icon="@mipmap/ic_launcher"
    android:theme="@style/AppTheme">

    <!--YOUR CODE HERE-->

    <!-- ADD LINE SDK Settings -->
    <activity
        android:name="jp.line.android.sdk.activity.LineAuthCompleteActivity"
        android:configChanges="keyboard|orientation"
        android:exported="true"
        android:screenOrientation="sensor" >
        <intent-filter>
            <action android:name="android.intent.action.VIEW" />

            <category android:name="android.intent.category.DEFAULT" />
            <category android:name="android.intent.category.BROWSABLE" />

            <data android:scheme="line.YOUR_CHANNEL_ID" />
        </intent-filter>
    </activity>
    <activity
        android:name="jp.line.android.sdk.activity.WebLoginActivity"
        android:configChanges="keyboard|orientation"
        android:exported="false"
        android:screenOrientation="sensor" >
    </activity>

    <meta-data
        android:name="jp.line.sdk.ChannelId"
        android:value="YOUR_CHANNEL_ID" />
    <meta-data
        android:name="jp.line.sdk.AuthScheme"
        android:value="line.YOUR_CHANNEL_ID" />
</application>
```

## Usage
```js
import { LoginManager } from 'react-native-line-login'

// use it
LoginManager.login()
.then((user) => {
  console.log(user)
})
.catch((err) => {
  console.log(err)
})
```
