/*
 *  LineAdapter.h
 *  LineAdapter
 *
 *  Created by han9kin on 2012-04-02.
 *  Copyright (c) 2012 NHN. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LineApiClient.h"

extern NSString *LineAdapterOtpIsReadyNotification;
extern NSString *LineAdapterAuthorizationDidChangeNotification;
extern NSString *const kLineAdapterVersion;

typedef enum LineAdapterPhase
{
    kLineBeta,
    kLineRC,
    kLineReal
} LineAdapterPhase;


@interface LineAdapter : NSObject


@property(nonatomic, readonly)                       BOOL      canAuthorizeUsingLineApp;

@property(nonatomic, readonly, copy)                 NSString *channelID;
@property(nonatomic, readonly, copy)                 NSString *MID;

@property(nonatomic, readonly, getter=isAuthorizing) BOOL      authorizing;
@property(nonatomic, readonly, getter=isAuthorized)  BOOL      authorized;

// A2A認証 ユーザーの操作結果が返ってきたときに実行されるべきメソッドです
+ (BOOL)handleLaunchOptions:(NSDictionary *)aLaunchOptions;
+ (BOOL)handleOpenURL:(NSURL *)aURL;

// 同じChannel ID, 同じPhaseの場合は同じインスタンスを返します
+ (instancetype)adapterWithConfigFile;
- (instancetype)initWithConfigFile;

- (void)installLineApp;
- (void)setPhase:(LineAdapterPhase)aPhase;

- (void)authorize; // for login
- (void)unauthorize; // for logout
- (void)authorizeWeb; // for login
- (void)clearLocalLoginInfo;

//- (void)cancel;

- (BOOL)handleLaunchOptions:(NSDictionary *)aLaunchOptions;
- (BOOL)handleOpenURL:(NSURL *)aURL;

- (LineApiClient *)getLineApiClient;

- (NSURLRequest *)requestWithPath:(NSString *)aPath HTTPMethod:(NSString *)aHTTPMethod parameters:(NSDictionary *)aParameters;
- (NSURLRequest *)requestForWebView;


@end
