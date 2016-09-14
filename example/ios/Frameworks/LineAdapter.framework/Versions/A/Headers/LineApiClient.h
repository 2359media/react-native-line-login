//
//  LineApiClient
//  LineAdapter
//
//  Created by Ueno Kenichi on 2013/08/20.
//  Copyright (c) 2013 LINE Corporation All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "LARequest.h"

/*! サーバーエラーを表します */
extern NSString *LineAdapterErrorDomain;

/*! Refresh成功時に発行されます
 * userInfo keys: mid, accessToken, refreshToken
 */
extern NSString *LineAdapterRefreshedTokenNotification;

/*! Auth Token失効時に発行されます。 
 * userInfo keys: 
 */
extern NSString *LineAdapterNoLongerAuthorizedNotification;

extern NSString *LineAdapterErrorStatusCode;
extern NSString *LineAdapterErrorStatusMessage;

typedef void (^lineadapter_response)(NSDictionary *aResult, NSError *aError);

typedef enum LineAdapterError
{
    kLineAdapterErrorNone,
    kLineAdapterErrorMissingConfiguration,
    kLineAdapterErrorAuthorizationAgentNotAvailable,
    kLineAdapterErrorInternalInconsistency,
    kLineAdapterErrorInvalidServerResponse,
    kLineAdapterErrorAuthorizationDenied,
    kLineAdapterErrorAuthorizationFailed,
    kLineAdapterErrorAuthorizationExpired,
    kLineAdapterErrorAccessTokenIsNotAvailable,
    kLineAdapterErrorNoLongerRefreshToken,
    kLineAdapterErrorUnknownError,
} LineAdapterError;

@interface LineApiClient : NSObject {
}

@property (nonatomic, strong) NSString *accessToken;
@property (nonatomic, strong) NSString *refreshToken;
@property (nonatomic, strong) NSDate   *expiresDate;
@property (nonatomic, strong) NSString *channelGatewayBaseURL;

@property (nonatomic, assign) int timeoutInterval;

// Core
- (void)postRequest:(LARequest *)aRequest
    completionBlock:(lineadapter_response)aCompletionBlock;

// login/logout
- (void)getOTPForChanneID:(NSString *)aChannelID
              resultBlock:(lineadapter_response)aResultBlock;

- (void)getAccessTokenForChannelID:(NSString *)aChannelID
                  withRequestToken:(NSString *)aRequestToken andOTP:(NSString *)aOTP resultBlock:(lineadapter_response)aResultBlock;

- (void)refreshWithResultBlock:(lineadapter_response)aResultBlock;


// API
- (void)getMyProfileWithResultBlock:(lineadapter_response)aResultBlock;

- (void)getMyFriendsForRange:(NSRange)aRange
                 resultBlock:(lineadapter_response)aResultBlock;

- (void)getMyFavoriteFriendsForRange:(NSRange)aRange
                         resultBlock:(lineadapter_response)aResultBlock;

- (void)getProfiles:(NSArray *)aMidArray
        resultBlock:(lineadapter_response)aResultBlock;

- (void)getSameChannelFriendsForRange:(NSRange)aRange
                          resultBlock:(lineadapter_response)aResultBlock;

- (void)uploadProfileImage:(UIImage *)aImage
                lowQuality:(BOOL)aLowQuality
               resultBlock:(lineadapter_response)aResultBlock;

- (void)postEventTo:(NSArray *)aMidArray
          toChannel:(NSString *)aChannelId
          eventType:(NSString *)aEventType
            content:(NSDictionary *)aContent
               push:(NSDictionary *)aPush
        resultBlock:(lineadapter_response)aResultBlock;

- (void)getGroupsForRange:(NSRange)aRange
              resultBlock:(lineadapter_response)aResultBlock;

- (void)getGroupMembers:(NSString *)aGroupMid
               forRange:(NSRange)aRange
            resultBlock:(lineadapter_response)aResultBlock;


@end
