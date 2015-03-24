//
//  AppDelegate.m
//  BoostMac
//
//  Created by lygv on 8/24/14.
//  Copyright (c) 2014 smartad. All rights reserved.
//

#import "AppDelegate.h"
#import "ASIFormDataRequest.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    countdownload = 0;
    max = 7000;
    for (int i=0; i<max; i++) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5*i * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            //[self downloadandroid];
            
            //[self download2:@"http://appvn.com/i/28853"]; //khung long
            //[self download:@"khung-long-chay-tron"];
            //[self viewApp:@"khung-long-chay-tron"];
            
            //[self download2:@"http://appvn.com/i/29207"]; //nguoi que
            [self viewApp:@"nguoi-que-nhay-vuot-rao"];
            [self download:@"nguoi-que-nhay-vuot-rao"];
            [self viewApp:@"dap-chuot-74"];
            [self download:@"dap-chuot-74"];
        });
    }
}


-(void)downloadandroid {
    NSString *urlstr = @"http://appvn.com/a/ajax/fdown/22901";
    NSURL *url = [NSURL URLWithString:urlstr];
    ASIFormDataRequest *req = [ASIFormDataRequest requestWithURL:url];
    NSString *cook = @"appota=a%3A12%3A%7Bs%3A10%3A%22session_id%22%3Bs%3A32%3A%22074cdbb6b3275c13f409ff206b77b192%22%3Bs%3A10%3A%22ip_address%22%3Bs%3A13%3A%22113.160.57.22%22%3Bs%3A10%3A%22user_agent%22%3Bs%3A81%3A%22Mozilla%2F5.0+%28Macintosh%3B+Intel+Mac+OS+X+10.9%3B+rv%3A31.0%29+Gecko%2F20100101+Firefox%2F31.0%22%3Bs%3A13%3A%22last_activity%22%3Bi%3A1407894311%3Bs%3A2%3A%22ip%22%3Bs%3A13%3A%22113.160.57.22%22%3Bs%3A17%3A%22appstore_feedback%22%3Bs%3A32%3A%22b6b76dfb75d4d4091a17480cb057f178%22%3Bs%3A12%3A%22app_feedback%22%3Bs%3A32%3A%22358816fe5fb78a68c5b8266abf5fe2b3%22%3Bs%3A16%3A%22appstore_comment%22%3Bs%3A32%3A%22bc8053498673363e45ef723633a02cc7%22%3Bs%3A9%3A%22logged_in%22%3Bi%3A1%3Bs%3A6%3A%22userid%22%3Bi%3A1063103%3Bs%3A8%3A%22username%22%3Bs%3A11%3A%22phihong1208%22%3Bs%3A5%3A%22uactk%22%3Bs%3A41%3A%2297836f0018f304bfb10990710c67f412053e981f5%22%3B%7D90b71ceef7834226ec7b98815958dafa; __utma=205977795.1394123373.1407719422.1407842956.1407894237.9; __utmz=205977795.1407719422.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); ci_session=aUiXEcaRtu%2B3X9QGKi1dJI47ib8tGP0eugZq34onzbqsnOOoGTxnGALUzbIvQWY549DFRchIIY%2F7weZenb8tpU8po2p0pCT2ZCp%2BTIFb5kVmGgB4P2y4Zht5JYG6YgHVE8qK5XCmEse1seALBKx7R7PnVAbRS1YDoVlY93pCqv9QrqsoANxes%2F4jdx%2B9VoaSjbGgLNCwfqerbusGDyIoye%2F%2BxX1Dp9kXpgrj34Iat2xOFPDEX5MxUxQPbvuMU6tse2%2FmEbQsWKX2SYajGvlRo28twTvkTAZmBxZfShLsA%2BeJfEvgaU1zN0cRgqncmBzvWwWxvIlrsEXPkKGmLnOatMsLW9%2BQYy21zuiSsK6xBywKhM1F5Q1MNmvj2d9pbMwcAhLgy36Ty0f%2FUWEudrGH6EeBp4%2FFUV5SY0m3zdQ1itz%2FHhfa9yFi2H1qpeQiW6lPrNzYB7uS1qWiJxgrjHh2IFYFoI1NqkZs4mT9c6fCx9sOBh%2BpDWnmF73%2FyDGKZ045LhbGmAfrYAksGpTNnCYE%2B30UhFfET7%2FWUn6VIwngem1sdFLjmLHUDBXl5xbjJtllgU6%2FwpJ87m9dxsuOsYjTkL2viYAsh6VKtnIsKwihTCwtMW4eKwevsIgRkNU9Cft%2F1QRBEb8Y4nw4MKdgTWw11seZyrUcFedK6GYkxlPFEnpyM1ueaq8diL2RWxHPzlUXS1rCjPfv23dFvTo43zUgOQ%3D%3D; __utmb=205977795.7.10.1407894237; SERVERID=A; PHPSESSID=dfr94p5pm502psv4bkfb9lkef5; countrytabs=0; countrytabs2=0; __utmc=205977795; _pk_id.1.cc1e=1dfb08623603a762.1407894400.1.1407894502.1407894400.; _pk_ses.1.cc1e=*; expandable=-1c";
    cook = @"__utma=205977795.1394123373.1407719422.1407842956.1407894237.9; __utmz=205977795.1407719422.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); ci_session=a%2FDw%2FeZSQf4cW0%2BnVZ2anF7GImpZe71TctTzB2ZtTNCLoK6SAvEtUUL23UxNqQXlR7CHvkM2vIQQ7LLq6Vvj%2Bcn9CMY85XM6ZjPiuYxtlQ6ruSShYbYilIuvhW%2F%2FmZDIUZrCBhPmyQ75FgJJaupI%2BOCI9w2pK9UhZA68sr0k8WaLrDcS0GNCRQF445QWjsFrZfG7ZvqV2c2VqM7jri9vnHzynre4rJpfwnpYbj8c7CmjwxOFm%2FjiC6WVPkiGmBEFsHAjDKruw0G6JfduawOD2Sl6TrBhlpjGoduLuBV0cS5D3nOjOnmS3Ms8596d35V1xGEFnYp6puM9BeQJBkLUjkQa%2BZFB1JL3K%2BUSa0aEqIWvhiasxght%2FzHHJeAL%2FbSCDgGrBznSadmBYuN7JVogE5uN38WjwATWA4QKkqc96YNqCRv1Y6ZYrfGtBeYmpm93ty%2FMlyHiNSEGFZDR88xImQXGWsmRW8AMmBkCpa3MYUy5cmDps6p%2BZ52DwI0VvZy9aI08Shhy6fPDLZkqQhIqljp7ytfjHkIqAohcJYi%2F2qYMcbP%2FRL9e3UDhr0O7q1G0O7QAKgCRz3secb1kRvqbsPs5JoBuma2KKHZxVI2rHPR3H%2FSqGMX%2BA%2B7LmGGXVELDcJTJGhCMIc7CEVR9w8PJEX6YraSC2f1JlNIE0efAkLV%2FwCSyj9D5cQHpHaNsrKOlxlw6q8UgjRhqUMYQffcF5A%3D%3D; __utmb=205977795.34.10.1407894237; SERVERID=A; PHPSESSID=dfr94p5pm502psv4bkfb9lkef5; countrytabs=0; countrytabs2=0; __utmc=205977795; _pk_id.1.cc1e=1dfb08623603a762.1407894400.1.1407897905.1407894400.; _pk_ses.1.cc1e=*; expandable=-1c; appota=a%3A5%3A%7Bs%3A10%3A%22session_id%22%3Bs%3A32%3A%22a12d512f1adafcde39046bd6ff832213%22%3Bs%3A10%3A%22ip_address%22%3Bs%3A13%3A%22113.160.57.22%22%3Bs%3A10%3A%22user_agent%22%3Bs%3A120%3A%22Mozilla%2F5.0+%28iPhone%3B+U%3B+CPU+iPhone+OS+3_0+like+Mac+OS+X%3B+en-us%29+AppleWebKit%2F528.18+%28KHTML%2C+like+Gecko%29+Version%2F4.0+Mobil%22%3Bs%3A13%3A%22last_activity%22%3Bi%3A1407897467%3Bs%3A2%3A%22ip%22%3Bs%3A13%3A%22113.160.57.22%22%3B%7D63295349bb2ba672a14c26a08f8ed33b";
    [req.requestHeaders setValue:cook forKey:@"Cookie"];
    [req.requestHeaders setValue:@"XMLHttpRequest" forKey:@"X-Requested-With"];
    [req setCompletionBlock:^{
        countdownload++;
        NSLog(@"response %@", req.responseString);
        NSLog(@"========================%s   countdownload2 %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
    }];
    [req setFailedBlock:^{
        NSLog(@"error %@", req.error);
        NSLog(@"========================%s   countdownload2 %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
        [self downloadandroid];
    }];
    [req startAsynchronous];
}

-(void)download2:(NSString*)applink {
    //NSString *urlstr = @"http://appvn.com/i/29207";//nguoi que
    //urlstr = @"http://appvn.com/i/28853";//khung long
    NSURL *url = [NSURL URLWithString:applink];
    ASIFormDataRequest *req = [ASIFormDataRequest requestWithURL:url];
    NSString *cook = @"appota=a%3A12%3A%7Bs%3A10%3A%22session_id%22%3Bs%3A32%3A%22074cdbb6b3275c13f409ff206b77b192%22%3Bs%3A10%3A%22ip_address%22%3Bs%3A13%3A%22113.160.57.22%22%3Bs%3A10%3A%22user_agent%22%3Bs%3A81%3A%22Mozilla%2F5.0+%28Macintosh%3B+Intel+Mac+OS+X+10.9%3B+rv%3A31.0%29+Gecko%2F20100101+Firefox%2F31.0%22%3Bs%3A13%3A%22last_activity%22%3Bi%3A1407894311%3Bs%3A2%3A%22ip%22%3Bs%3A13%3A%22113.160.57.22%22%3Bs%3A17%3A%22appstore_feedback%22%3Bs%3A32%3A%22b6b76dfb75d4d4091a17480cb057f178%22%3Bs%3A12%3A%22app_feedback%22%3Bs%3A32%3A%22358816fe5fb78a68c5b8266abf5fe2b3%22%3Bs%3A16%3A%22appstore_comment%22%3Bs%3A32%3A%22bc8053498673363e45ef723633a02cc7%22%3Bs%3A9%3A%22logged_in%22%3Bi%3A1%3Bs%3A6%3A%22userid%22%3Bi%3A1063103%3Bs%3A8%3A%22username%22%3Bs%3A11%3A%22phihong1208%22%3Bs%3A5%3A%22uactk%22%3Bs%3A41%3A%2297836f0018f304bfb10990710c67f412053e981f5%22%3B%7D90b71ceef7834226ec7b98815958dafa; __utma=205977795.1394123373.1407719422.1407842956.1407894237.9; __utmz=205977795.1407719422.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); ci_session=aUiXEcaRtu%2B3X9QGKi1dJI47ib8tGP0eugZq34onzbqsnOOoGTxnGALUzbIvQWY549DFRchIIY%2F7weZenb8tpU8po2p0pCT2ZCp%2BTIFb5kVmGgB4P2y4Zht5JYG6YgHVE8qK5XCmEse1seALBKx7R7PnVAbRS1YDoVlY93pCqv9QrqsoANxes%2F4jdx%2B9VoaSjbGgLNCwfqerbusGDyIoye%2F%2BxX1Dp9kXpgrj34Iat2xOFPDEX5MxUxQPbvuMU6tse2%2FmEbQsWKX2SYajGvlRo28twTvkTAZmBxZfShLsA%2BeJfEvgaU1zN0cRgqncmBzvWwWxvIlrsEXPkKGmLnOatMsLW9%2BQYy21zuiSsK6xBywKhM1F5Q1MNmvj2d9pbMwcAhLgy36Ty0f%2FUWEudrGH6EeBp4%2FFUV5SY0m3zdQ1itz%2FHhfa9yFi2H1qpeQiW6lPrNzYB7uS1qWiJxgrjHh2IFYFoI1NqkZs4mT9c6fCx9sOBh%2BpDWnmF73%2FyDGKZ045LhbGmAfrYAksGpTNnCYE%2B30UhFfET7%2FWUn6VIwngem1sdFLjmLHUDBXl5xbjJtllgU6%2FwpJ87m9dxsuOsYjTkL2viYAsh6VKtnIsKwihTCwtMW4eKwevsIgRkNU9Cft%2F1QRBEb8Y4nw4MKdgTWw11seZyrUcFedK6GYkxlPFEnpyM1ueaq8diL2RWxHPzlUXS1rCjPfv23dFvTo43zUgOQ%3D%3D; __utmb=205977795.7.10.1407894237; SERVERID=A; PHPSESSID=dfr94p5pm502psv4bkfb9lkef5; countrytabs=0; countrytabs2=0; __utmc=205977795; _pk_id.1.cc1e=1dfb08623603a762.1407894400.1.1407894502.1407894400.; _pk_ses.1.cc1e=*; expandable=-1c";
    cook = @"__utma=205977795.1394123373.1407719422.1407842956.1407894237.9; __utmz=205977795.1407719422.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); ci_session=a%2FDw%2FeZSQf4cW0%2BnVZ2anF7GImpZe71TctTzB2ZtTNCLoK6SAvEtUUL23UxNqQXlR7CHvkM2vIQQ7LLq6Vvj%2Bcn9CMY85XM6ZjPiuYxtlQ6ruSShYbYilIuvhW%2F%2FmZDIUZrCBhPmyQ75FgJJaupI%2BOCI9w2pK9UhZA68sr0k8WaLrDcS0GNCRQF445QWjsFrZfG7ZvqV2c2VqM7jri9vnHzynre4rJpfwnpYbj8c7CmjwxOFm%2FjiC6WVPkiGmBEFsHAjDKruw0G6JfduawOD2Sl6TrBhlpjGoduLuBV0cS5D3nOjOnmS3Ms8596d35V1xGEFnYp6puM9BeQJBkLUjkQa%2BZFB1JL3K%2BUSa0aEqIWvhiasxght%2FzHHJeAL%2FbSCDgGrBznSadmBYuN7JVogE5uN38WjwATWA4QKkqc96YNqCRv1Y6ZYrfGtBeYmpm93ty%2FMlyHiNSEGFZDR88xImQXGWsmRW8AMmBkCpa3MYUy5cmDps6p%2BZ52DwI0VvZy9aI08Shhy6fPDLZkqQhIqljp7ytfjHkIqAohcJYi%2F2qYMcbP%2FRL9e3UDhr0O7q1G0O7QAKgCRz3secb1kRvqbsPs5JoBuma2KKHZxVI2rHPR3H%2FSqGMX%2BA%2B7LmGGXVELDcJTJGhCMIc7CEVR9w8PJEX6YraSC2f1JlNIE0efAkLV%2FwCSyj9D5cQHpHaNsrKOlxlw6q8UgjRhqUMYQffcF5A%3D%3D; __utmb=205977795.34.10.1407894237; SERVERID=A; PHPSESSID=dfr94p5pm502psv4bkfb9lkef5; countrytabs=0; countrytabs2=0; __utmc=205977795; _pk_id.1.cc1e=1dfb08623603a762.1407894400.1.1407897905.1407894400.; _pk_ses.1.cc1e=*; expandable=-1c; appota=a%3A5%3A%7Bs%3A10%3A%22session_id%22%3Bs%3A32%3A%22a12d512f1adafcde39046bd6ff832213%22%3Bs%3A10%3A%22ip_address%22%3Bs%3A13%3A%22113.160.57.22%22%3Bs%3A10%3A%22user_agent%22%3Bs%3A120%3A%22Mozilla%2F5.0+%28iPhone%3B+U%3B+CPU+iPhone+OS+3_0+like+Mac+OS+X%3B+en-us%29+AppleWebKit%2F528.18+%28KHTML%2C+like+Gecko%29+Version%2F4.0+Mobil%22%3Bs%3A13%3A%22last_activity%22%3Bi%3A1407897467%3Bs%3A2%3A%22ip%22%3Bs%3A13%3A%22113.160.57.22%22%3B%7D63295349bb2ba672a14c26a08f8ed33b";
    [req.requestHeaders setValue:cook forKey:@"Cookie"];
    [req.requestHeaders setValue:@"XMLHttpRequest" forKey:@"X-Requested-With"];
    [req setCompletionBlock:^{
        countdownload++;
        NSLog(@"response %@", req.responseString);
        NSLog(@"========================%s   countdownload2 %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
    }];
    [req setFailedBlock:^{
        NSLog(@"error %@", req.error);
        NSLog(@"========================%s   countdownload2 %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
        [self download2:applink];
    }];
    [req startAsynchronous];
}

-(void)viewApp:(NSString*)appname {
    NSURL *url = [NSURL URLWithString:@"https://api.appota.com/content/detail?access_token=569df25deda0a7b1d4db8638c0a01187053e70ea8&lang=vi"];
    ASIFormDataRequest *req = [ASIFormDataRequest requestWithURL:url];
    [req setPostValue:@"false" forKey:@"version_list"];
    [req setPostValue:appname forKey:@"application"];
    [req setPostValue:@"appota_ios_nonjb" forKey:@"client"];
    [req setPostValue:@"0" forKey:@"kids_lock"];
    [req setPostValue:@"688B6F87-97A1-4070-A09C-906F2809426A" forKey:@"device_id"];
    [req setPostValue:@"home" forKey:@"referer"];
    [req setPostValue:@"true" forKey:@"force_cache"];
    [req setCompletionBlock:^{
        countdownload++;
        NSLog(@"response %@", req.responseString);
        NSLog(@"========================%s   countview %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
    }];
    [req setFailedBlock:^{
        NSLog(@"error %@", req.error);
        NSLog(@"========================%s   countview %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
        [self viewApp:appname];
    }];
    [req startAsynchronous];
}

-(void)download:(NSString*)appname {
    NSURL *url = [NSURL URLWithString:@"https://api.appota.com/content/download?access_token=569df25deda0a7b1d4db8638c0a01187053e70ea8&lang=vi"];
    ASIFormDataRequest *req = [ASIFormDataRequest requestWithURL:url];
    [req setPostValue:@"home" forKey:@"referer"];
    [req setPostValue:appname forKey:@"application"];
    [req setPostValue:@"appota_ios_nonjb" forKey:@"client"];
    [req setPostValue:@"0" forKey:@"machine_status"];
    [req setPostValue:@"688B6F87-97A1-4070-A09C-906F2809426A" forKey:@"device_id"];
    [req setPostValue:@"sopcast" forKey:@"store"];
    [req setPostValue:@"521261" forKey:@"version"];
    [req setCompletionBlock:^{
        countdownload++;
        NSLog(@"response %@", req.responseString);
        NSLog(@"========================%s   countdownload %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
    }];
    [req setFailedBlock:^{
        NSLog(@"error %@", req.error);
        NSLog(@"========================%s   countdownload %d", __func__, countdownload);
        text.stringValue = [NSString stringWithFormat:@"%s count %d", __func__, countdownload];
        [self download:appname];
    }];
    [req startAsynchronous];
}

@end
