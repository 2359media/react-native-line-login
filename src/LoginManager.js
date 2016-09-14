/**
 * @flow
 */
'use strict';

const LoginManager = require('react-native').NativeModules.RNLineLoginManager;

/**
 * Shows the results of a login operation.
 */
export type LoginResult = {
  accessToken: string,
  refreshToken: string,
  expire: string,
  mid: string
};

/**
 * UserProfile
 */
export type Profile = {
  displayName: string,
  mid: string,
  pictureUrl: string
}

module.exports = {
  /**
   * Logs the user in with the requested read permissions.
   */
  login(): Promise<LoginResult> {
    return LoginManager.login();
  },

  /**
   * Get user profile
   */
  getUserProfile(): Promise<Profile> {
    return LoginManager.getUserProfile();
  },  

  /**
   * Logs out the user.
   */
  logout() {
    LoginManager.logout();
  },
};