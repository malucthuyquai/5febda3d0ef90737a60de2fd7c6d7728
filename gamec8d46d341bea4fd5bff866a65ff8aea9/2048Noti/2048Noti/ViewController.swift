//
//  ViewController.swift
//  2048Noti
//
//  Created by LyGV on 11/20/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    var game:NumberTileGameViewController?
    override func viewDidLoad() {
        super.viewDidLoad()
        game = NumberTileGameViewController(dimension: 4, threshold: 2048)
        game?.view.center = self.view.center;
        view.addSubview(game!.view)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

