//
//  AppDelegate.m
//  Zing
//
//  Created by LyGV on 4/8/13.
//  Copyright (c) 2013 LyGV. All rights reserved.
//

#import "AppDelegate.h"
#import "HTMLParser.h"
#import "AFNetworking.h"

@implementation AppDelegate
@synthesize page, pageinput, song, title, percent;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    NSUserDefaults *df = [NSUserDefaults standardUserDefaults];
    pageindex = [[df objectForKey:@"page"] intValue];
    pageinput.stringValue = [NSString stringWithFormat:@"%d", pageindex];
    page.stringValue = [NSString stringWithFormat:@"%d", pageindex];
    songindex = 0;
    songarray = [[NSMutableArray alloc] init];
}

-(IBAction)start:(id)sender{
    pageindex = [pageinput.stringValue intValue];
    songindex = 0;
    [self downloadpage];
}

-(void)downloadpage{
    pageinput.stringValue = [NSString stringWithFormat:@"%d", pageindex];
    page.stringValue = [NSString stringWithFormat:@"%d", pageindex];
    
    NSUserDefaults *df = [NSUserDefaults standardUserDefaults];
    [df setValue:page.stringValue forKey:@"page"];
    [df synchronize];
    
    NSString *urlstring = [NSString stringWithFormat:@"http://star.zing.vn/star/phongthu/index.html?page=%d&alpha=all&sort=time", pageindex];
    NSString *html = [NSString stringWithContentsOfURL:[NSURL URLWithString:urlstring] encoding:NSUTF8StringEncoding error:nil];
    NSError *error;
    HTMLParser *parser = [[HTMLParser alloc] initWithString:html error:&error];
    
    if (error) {
        NSLog(@"%s Error: %@", __func__, error);
        return;
    }
    
    HTMLNode *bodyNode = [parser body];
    
    NSArray *inputNodes = [bodyNode findChildTags:@"a"];
    
    for (HTMLNode *inputNode in inputNodes) {
        if ([[inputNode getAttributeNamed:@"class"] isEqualToString:@"font_12 bold"]) {
            NSString *songurlstring = [inputNode getAttributeNamed:@"href"];
            [songarray addObject:songurlstring];
        }
    }
    
    [self downloadSong];
}

-(void)downloadSong{
    page.stringValue = [NSString stringWithFormat:@"%d", pageindex];
    if ([songarray count] > 0) {
        NSString *path = @"/Users/lygv/Desktop/Zing/Zing/data";
        NSLog(@"count %ld", (unsigned long)[songarray count]);
        NSString *songurlstring = [songarray objectAtIndex:0];
        [songarray removeObjectAtIndex:0];
        songindex++;
        
        song.stringValue = [NSString stringWithFormat:@"%d", songindex];
        
        songurlstring = [songurlstring stringByReplacingOccurrencesOfString:@".html" withString:@""];
        
        title.stringValue = [[songurlstring componentsSeparatedByString:@"/"] lastObject];
        
        NSString *songid = [[songurlstring componentsSeparatedByString:@"."] lastObject];
        
        songurlstring = [NSString stringWithFormat:@"http://star.zing.vn/includes/fnGetSongInfo.php?id=%@", songid];
        NSLog(@"start download %@", songurlstring);
        
        NSString *html = [NSString stringWithContentsOfURL:[NSURL URLWithString:songurlstring] encoding:NSUTF8StringEncoding error:nil];
        
        NSString *xml = [NSString stringWithFormat:@"<!DOCTYPE html>\n<html><head><title></title></head><body>%@</body></html>", html];
        
        NSError *error;
        HTMLParser *parser = [[HTMLParser alloc] initWithString:xml error:&error];
        
        if (error) {
            NSLog(@"%s Error1: %@", __func__, error);
            return;
        }
        HTMLNode *bodyNode = [parser body];
        
        HTMLNode *lyric = [bodyNode findChildTag:@"lyric"];
        NSString *lyricname = [[lyric.contents componentsSeparatedByString:@"/"] lastObject];
        
        HTMLNode *beat = [bodyNode findChildTag:@"karaokelink"];
        NSString *beatname = [[beat.contents componentsSeparatedByString:@"/"] lastObject];
        
        HTMLNode *skin = [bodyNode findChildTag:@"skin"];
        //NSString *skinname = [[beat.contents componentsSeparatedByString:@"/"] lastObject];
        
        html = [html stringByReplacingOccurrencesOfString:lyric.contents withString:[NSString stringWithFormat:@"../data/%@", lyricname]];
        html = [html stringByReplacingOccurrencesOfString:beat.contents withString:[NSString stringWithFormat:@"../data/%@", beatname]];
        html = [html stringByReplacingOccurrencesOfString:@"</karaokelink>" withString:[NSString stringWithFormat:@"</karaokelink>\n		<id>%@</id>", songid]];
        html = [html stringByReplacingOccurrencesOfString:[NSString stringWithFormat:@"<skin>%@</skin>",skin.contents] withString:@"<skin>../flash/</skin>"];
        
        NSString *inf = [path stringByAppendingFormat:@"/%@.inf", songid];
        [html writeToFile:inf atomically:NO encoding:NSUTF8StringEncoding error:nil];
        
        //Init request to get data
        NSURL *url = [NSURL URLWithString:lyric.contents];
        NSLog(@"lyric %@", lyric.contents);
        AFHTTPClient *client = [AFHTTPClient clientWithBaseURL:url];
        [client setParameterEncoding:AFFormURLParameterEncoding];
        NSMutableURLRequest *request = [client requestWithMethod:@"GET" path:lyric.contents parameters:nil];
        
        [client registerHTTPOperationClass:[AFHTTPRequestOperation class]];
        
        //Begin send request to get data from url
        AFHTTPRequestOperation *operation = [client HTTPRequestOperationWithRequest:request success:^(AFHTTPRequestOperation *operation, id responseObject) {
            NSString *lyricfile = [path stringByAppendingFormat:@"/%@", lyricname];
            [responseObject writeToFile:lyricfile atomically:NO];
            //Continue for next file
        } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
            //NSLog(@"Error: %@", error.localizedDescription);
        }];
        //End send request to get data from url
        
        [client enqueueHTTPRequestOperation:operation];
        
        
        //Init request to get data
        NSURL *url1 = [NSURL URLWithString:beat.contents];
        AFHTTPClient *client1 = [AFHTTPClient clientWithBaseURL:url1];
        [client1 setParameterEncoding:AFFormURLParameterEncoding];
        NSMutableURLRequest *request1 = [client1 requestWithMethod:@"GET" path:beat.contents parameters:nil];
        
        [client1 registerHTTPOperationClass:[AFHTTPRequestOperation class]];
        
        //Begin send request to get data from url
        AFHTTPRequestOperation *operation1 = [client1 HTTPRequestOperationWithRequest:request1 success:^(AFHTTPRequestOperation *operation, id responseObject) {
            NSString *beatfile = [path stringByAppendingFormat:@"/%@", beatname];
            [responseObject writeToFile:beatfile atomically:NO];
            //Continue for next file
            NSLog(@"success");
            [self downloadSong];
        } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
            NSLog(@"error");
            //Continue for next file
            [self downloadSong];
            //NSLog(@"Error: %@", error.localizedDescription);
        }];
        //End send request to get data from url
        
        //The following codes allow you to track the download progress (if required)
        [operation1 setDownloadProgressBlock:^(NSUInteger bytesRead, long long totalBytesRead, long long totalBytesExpectedToRead) {
            float p = totalBytesRead * 1.0 / totalBytesExpectedToRead * 1.0;
            percent.stringValue = [NSString stringWithFormat:@"%2.0f", p*100];
        }];
        //End of the download progress tracking code
        
        [client1 enqueueHTTPRequestOperation:operation1];
        
    } else {
        pageindex++;
        songindex = 0;
        [self downloadpage];
    }
}









@end
