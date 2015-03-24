//
//  InstagramLoginDelegate.m
//  NRGramKit
//
//  Created by Raul Andrisan on 5/23/12.
//  Copyright (c) 2012 NextRoot. All rights reserved.
//

#import "InstagramLoginDelegate.h"

@interface InstagramLoginDelegate (){
    NSString* callbackURL;
}

@end

@implementation InstagramLoginDelegate

@synthesize onSuccess;
@synthesize onError;
@synthesize onLoadingChanged;

- (id)init
{
    self = [super init];
    if (self) {
        NSBundle *bd = [NSBundle mainBundle];
        NSString* urlString = [[bd infoDictionary] objectForKey:@"InstagramClientCallbackURL"];
        NSURL* url = [NSURL URLWithString:urlString];
        callbackURL = [url host];
    }
    return self;
}
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSString* host = [[request URL] host];
    if([host rangeOfString:callbackURL].location!=NSNotFound)
    {
        NSString* frag = [[request URL] fragment];
        NSMutableDictionary*dict = [self parseQueryString:frag];
        NSString* accessToken = [dict objectForKey:@"access_token"];
        onSuccess(accessToken);
        return NO;
    }
    
    return YES;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    onLoadingChanged(YES);
}
- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    onLoadingChanged(NO);
    if ([webView.request.URL.absoluteString rangeOfString:@"login"].location == NSNotFound) {
        NSString *javascript = [NSString stringWithFormat:@"document.body.style.width = \"320px\"; document.body.style.height = \"568px\"; document.getElementsByClassName(\"root\")[0].style.marginLeft=\"0px\"; document.getElementsByClassName(\"actions\")[0].style.right=\"0px\""];
        [webView stringByEvaluatingJavaScriptFromString:javascript];
    }
}
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    NSString* failedUrl = error.userInfo[@"NSErrorFailingURLStringKey"];
    if([failedUrl rangeOfString:callbackURL].location==NSNotFound)
    {
        onError([error localizedDescription]);
    }
    if ([webView.request.URL.absoluteString rangeOfString:@"login"].location == NSNotFound) {
        NSString *javascript = [NSString stringWithFormat:@"document.body.style.width = \"320px\"; document.body.style.height = \"568px\"; document.getElementsByClassName(\"root\")[0].style.marginLeft=\"0px\"; document.getElementsByClassName(\"actions\")[0].style.right=\"0px\""];
        [webView stringByEvaluatingJavaScriptFromString:javascript];
    }
}

-(NSMutableDictionary *)parseQueryString:(NSString *)query {
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] initWithCapacity:6];
    NSArray *pairs = [query componentsSeparatedByString:@"&amp;"];
    
    for (NSString *pair in pairs) {
        NSArray *elements = [pair componentsSeparatedByString:@"="];
        NSString *key = [[elements objectAtIndex:0] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        NSString *val = [[elements objectAtIndex:1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        
        [dict setObject:val forKey:key];
    }
    return dict;
}


@end
