//
//  TodayViewController.swift
//  2048Ext
//
//  Created by LyGV on 11/20/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

import UIKit
import NotificationCenter
import GameKit

class TodayViewController: UIViewController, NCWidgetProviding, GKGameCenterControllerDelegate {
    var game:NumberTileGameViewController?
    override func viewDidLoad() {
        super.viewDidLoad()
        self.preferredContentSize = CGSizeMake(0, 480)
        game = NumberTileGameViewController(dimension: 4, threshold: 2048)
        game?.view.center = self.view.center;
        view.insertSubview(game!.view, atIndex: 0)
        

    }
    
    @IBAction func up(x:UIButton) {
        game?.upCommand(nil)
    }
    @IBAction func down(x:UIButton) {
        game?.downCommand(nil)
    }
    @IBAction func left(x:UIButton) {
        game?.leftCommand(nil)
    }
    @IBAction func right(x:UIButton) {
        game?.rightCommand(nil)
    }
    
    func gameCenterViewControllerDidFinish(gameCenterViewController: GKGameCenterViewController!)
    {
        gameCenterViewController.dismissViewControllerAnimated(true, completion: nil)
    }
    
    func showLeaderboard()
    {
        var gcViewController: GKGameCenterViewController = GKGameCenterViewController()
        gcViewController.gameCenterDelegate = self
        
        gcViewController.viewState = GKGameCenterViewControllerState.Leaderboards
        gcViewController.leaderboardIdentifier = "mobi.smartad.2048"
        
        self.presentViewController(gcViewController, animated: true, completion: nil)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func widgetPerformUpdateWithCompletionHandler(completionHandler: ((NCUpdateResult) -> Void)!) {

        completionHandler(NCUpdateResult.NewData)
    }
    
}
