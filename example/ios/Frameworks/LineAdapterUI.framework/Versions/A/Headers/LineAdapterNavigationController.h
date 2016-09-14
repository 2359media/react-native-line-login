/*
 *  LineAdapterNavigationController.h
 *  LineAdapterUI
 *
 *  Created by han9kin on 2012-07-18.
 *  Copyright (c) 2012 NHN. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>


@interface LineAdapterNavigationController : UINavigationController


+ (UIBarButtonItem *)barButtonItemWithImage:(UIImage *)aImage target:(id)aTarget action:(SEL)aAction;
+ (UIBarButtonItem *)barButtonItemWithTitle:(NSString *)aTitle target:(id)aTarget action:(SEL)aAction;


@end
