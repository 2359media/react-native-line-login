//
//  LARequest.h
//  LineAdapter
//
//  Created by Ueno Kenichi on 2013/08/21.
//  Copyright (c) 2013年 NHN. All rights reserved.
//  API how to use : https://developers.line.me/how-to-develop-channel-application/line-sdk-for-ios-version-3
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, LARequestType){
    LARequestTypeUndefined,
    
    LARequestTypeGetOTP,
    LARequestTypeGetAccessToken,
    LARequestTypeRefresh,
    
    LARequestTypeGetMyProfile,
    LARequestTypeGetMyFriends,
    LARequestTypeGetMyFavoriteFriends,
    LARequestTypeGetProfiles,
    LARequestTypeGetSameChannelFriends,
    LARequestTypeUploadProfileImage,
    LARequestTypePostEvent,
    LARequestTypeGetGroups,
    LARequestTypeGetGroupMembers,
};

@interface LARequest : NSObject

@property (nonatomic, assign) LARequestType type;
@property (nonatomic, strong) NSString *protocol;
@property (nonatomic, strong) NSString *method;

@property (nonatomic, strong) NSData *contentData;
@property (nonatomic, strong) NSDictionary *parameters;

+ (instancetype)requestForGetOTPForChannelID:(NSString *)aChannelID;
+ (instancetype)requestForGetAccessTokenForChannelID:(NSString *)aChannelID
                                    withRequestToken:(NSString *)aRequestToken
                                              andOTP:(NSString *)aOTP;
+ (instancetype)requestForRefreshWithRefreshToken:(NSString *)aRefreshToken;

#pragma mark - Get user profile
+ (instancetype)requestForGetMyProfile;

#pragma mark - Upload profile image
+ (instancetype)requestForUploadProfileImage:(UIImage *)aImage
                                    compress:(CGFloat)aCompress;

#pragma mark - Access to Social Graph
+ (instancetype)requestForGetMyFriendsForRange:(NSRange)aRange;
+ (instancetype)requestForGetMyFavoriteFriendsForRange:(NSRange)aRange;


#pragma mark - Post event
+ (instancetype)requestForPostEventTo:(NSArray *)aMidArray
                            toChannel:(NSInteger)aChannelId
                            eventType:(NSString *)aEventType
                              content:(NSDictionary *)aContent
                                 push:(NSDictionary *)aPush;

#pragma mark - Get Group information
+ (instancetype)requestForGetGroupsForRange:(NSRange)aRange;
+ (instancetype)requestForGetGroupMembers:(NSString *)aGroupMid
                                 forRange:(NSRange)aRange;

#pragma mark - Not listed yet?
+ (instancetype)requestForGetProfiles:(NSArray *)aMidArray;
+ (instancetype)requestForGetSameChannelFriendsForRange:(NSRange)aRange;


@end
