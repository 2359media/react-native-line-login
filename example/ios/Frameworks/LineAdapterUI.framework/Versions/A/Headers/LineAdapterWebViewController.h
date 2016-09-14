//
//  LineAdapterWebViewController.h
//  LineAdapterUI
//
//  Created by 홍석주 on 12. 10. 15..
//  Copyright (c) 2012년 NHN. All rights reserved.
//

#import <UIKit/UIKit.h>


@class LineAdapter;


typedef enum WebViewOrientation
{
    kOrientationPortrait,
    kOrientationLandscape,
    kOrientationAll
} WebViewOrientation;


@interface LineAdapterWebViewController : UIViewController <UIWebViewDelegate>

- (id)initWithAdapter:(LineAdapter *)aAdapter withWebViewOrientation:(WebViewOrientation)aWebViewOrientation;
- (NSUInteger)supportedOrientation;
- (BOOL)supportedShouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)aInterfaceOrientation;

@end
