# iOS Guide
Includes LINE iOS SDK v3.1.17

## LINE Getting Started Guide
- [https://developers.line.me/ios/development-with-sdk](https://developers.line.me/ios/development-with-sdk)


## Setup
- [Do all the steps in LINE document page](https://developers.line.me/ios/development-with-sdk)
- [Link the library](https://facebook.github.io/react-native/docs/linking-libraries-ios.html#manual-linking)

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
