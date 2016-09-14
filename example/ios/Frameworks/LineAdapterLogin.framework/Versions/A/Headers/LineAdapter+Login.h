/*
 *  LineAdapter+Login.h
 *  LineAdapterLogin
 *
 *  Created by han9kin on 2012-07-10.
 *  Copyright (c) 2012 NHN. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <LineAdapter/LineAdapter.h>


extern NSString *LineAdapterRequireUserApprovalNotification;
extern NSString *LineAdapterUserApprovalDidFinishNotification;


@interface LineAdapter (Login)


- (void)loginWithID:(NSString *)aUserID password:(NSString *)aPassword isNaverID:(BOOL)aNaverID;

- (NSURL *)returnURLWithAuthorizationResultURL:(NSURL *)aURL;

@end
