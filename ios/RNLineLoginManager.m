
#import "RNLineLoginManager.h"
#import <LineAdapter/LineAdapter.h>
#import <LineAdapterUI/LineAdapterUI.h>

@interface RNLineLoginManager ()
@property (strong, nonatomic) RCTPromiseResolveBlock loginResolver;
@property (strong, nonatomic) RCTPromiseRejectBlock loginRejecter;
@property (strong, nonatomic) LineAdapter *adapter;
@property (strong, nonatomic) UIViewController *navigationController;
@end

@implementation RNLineLoginManager

#pragma mark - Object life cyle

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}


RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(login:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    self.loginResolver = resolve;
    self.loginRejecter = reject;
    
    [self login];
}

RCT_EXPORT_METHOD(getUserProfile:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    [self getUserProfileInfo:resolve rejecter:reject];
}

RCT_EXPORT_METHOD(logout)
{
    [self.adapter unauthorize];
}

//initialize LINE sdk
- (id) init {
    self = [super init];
    if (self)
    {
        _adapter = [[LineAdapter alloc] initWithConfigFile];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(lineAdapterAuthorizationDidChange:)
                                                     name:LineAdapterAuthorizationDidChangeNotification object:nil];
        
    }
    return self;
}

- (void) cancel:(id)sender {
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
    if (self.loginRejecter) {
        self.loginRejecter(@"LineSDK", @"Login Line Canceled", nil);
    }
}

#pragma mark - Login

- (void)login
{
    if ([self.adapter isAuthorized]) {
        self.loginResolver([self getUserTokenInfo]);
    } else {
        [self handleAuthorization];
    }
}

- (void)handleAuthorization
{
    if ([self.adapter canAuthorizeUsingLineApp])
    {
        // Authenticate with LINE application
        [self.adapter authorize];
    }
    else
    {
        // Authenticate with WebView
        UIViewController *viewController;
        viewController = [[LineAdapterWebViewController alloc] initWithAdapter:self.adapter
                                                        withWebViewOrientation:kOrientationAll];
        [[viewController navigationItem] setLeftBarButtonItem:[LineAdapterNavigationController
                                                               barButtonItemWithTitle:@"Cancel" target:self action:@selector(cancel:)]];
        
        self.navigationController = [[LineAdapterNavigationController alloc]
                                     initWithRootViewController:viewController];
        
        // get current view controller
        id rootViewController = [[[UIApplication sharedApplication] keyWindow] rootViewController];
        if ([rootViewController isKindOfClass:[UIViewController class]]) {
            rootViewController = (UINavigationController *)[[[UIApplication sharedApplication] keyWindow] rootViewController];
            [rootViewController presentViewController:self.navigationController animated:YES completion:nil];
        } else {
            NSLog(@"rootViewController is not a navigation controller instance");
        }
    }

}

- (NSDictionary *) getUserTokenInfo {
    LineApiClient *apiClient = [self.adapter getLineApiClient];
    NSDictionary *userTokenInfo = @{
                                    @"mid" : self.adapter.MID,
                                    @"accessToken" : apiClient.accessToken,
                                    @"refreshToken" : apiClient.refreshToken,
                                    @"expire" : [NSString stringWithFormat:@"%@", apiClient.expiresDate]
                                   };
    return userTokenInfo;
}

- (void)lineAdapterAuthorizationDidChange:(NSNotification*)aNotification
{
    LineAdapter *_adapter = [aNotification object];
    if ([_adapter isAuthorized])
    {
        NSLog(@"Login success");
        [self.navigationController dismissViewControllerAnimated:YES completion:nil];
        if (self.loginResolver) {
            self.loginResolver([self getUserTokenInfo]);
        }
    }
    else
    {
        NSError *error = [[aNotification userInfo] objectForKey:@"error"];
        if (error)
        {
            NSLog(@"Login failed");
            
            [self.navigationController dismissViewControllerAnimated:YES completion:nil];
            if (self.loginRejecter) {
                self.loginRejecter(@"LineSDK", @"Login Line Failed", error);
            }
            
            NSString *errorMessage = [error localizedDescription];
            NSInteger code = [error code];
            if (code == kLineAdapterErrorMissingConfiguration)
            {
                // URL Types is not set correctly
            }
            else if (code == kLineAdapterErrorAuthorizationAgentNotAvailable)
            {
                // The LINE application is not installed
            }
            else if (code == kLineAdapterErrorInvalidServerResponse)
            {
                // The response from the server is incorrect
            }
            else if (code == kLineAdapterErrorAuthorizationDenied)
            {
                // The user has cancelled the authentication and authorization
            }
            else if (code == kLineAdapterErrorAuthorizationFailed)
            {
                // The authentication and authorization has failed for an unknown reason
            }
        }
    }
}

- (void) getUserProfileInfo:(RCTPromiseResolveBlock)resolve
                          rejecter:(RCTPromiseRejectBlock)reject
{
    [[self.adapter getLineApiClient] getMyProfileWithResultBlock:^(NSDictionary *aResult, NSError *aError)
     {
         if (aResult)
         {
             // API call was successfully.
             resolve(aResult);
             
         }
         else
         {
             // API call failed.
             reject(@"LineSDK", @"Failed to get user profile", aError);
         }
     }];
}
@end
  