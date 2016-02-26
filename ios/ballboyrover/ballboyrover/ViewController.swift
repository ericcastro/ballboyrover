//
//  ViewController.swift
//  ballboyrover
//
//  Created by Eric Castro on 24/02/16.
//  Copyright © 2016 Eric Castro. All rights reserved.
//

import UIKit
import GameController


class ViewController: UIViewController {
    
    var profile:GCExtendedGamepad? = nil
    var connMgr = ConnectionManager.sharedInstance

    var armRotationDirection = 1;
    var armRotationSpeed = 0.0;
    var armRotationEngaged = false

    var armLiftDirection = 1;
    var armLiftSpeed = 0.0;
    var armLiftEngaged = false

    var armGripDirection = 1;
    var armGripSpeed = 0.0;
    var armGripEngaged = false

    override func viewDidLoad() {
        super.viewDidLoad()
        
        NSNotificationCenter.defaultCenter().addObserverForName(GCControllerDidConnectNotification, object: nil, queue: nil) { (n) -> Void in
            
            print("Controller connected! \(n.object)")
            
            let controller:GCController = n.object as! GCController
            
            self.profile = controller.extendedGamepad;
            
            self.profile?.valueChangedHandler = {
                (gamepad: GCExtendedGamepad, element: GCControllerElement) -> Void in
                /*var lx = self.profile?.leftThumbstick.xAxis.value
                var ly = self.profile?.leftThumbstick.yAxis.value

                var result1: Float = 0.0
                var result2: Float = 0.0

                result1 = ly! - lx!
                result2 = lx! + ly!

                print("\(Int(result2 * 128)) \(Int(result1 * 128))")*/

                var dpad_up = self.profile?.dpad.up.value
                var dpad_down = self.profile?.dpad.down.value
                var dpad_left = self.profile?.dpad.left.value
                var dpad_right = self.profile?.dpad.right.value
                var l2 = self.profile?.leftTrigger.value
                var r2 = self.profile?.rightTrigger.value

                var cmd:String = ""
                if dpad_left == 0.0 && dpad_right == 0.0 {
                    if self.armRotationEngaged {
                        self.armRotationEngaged = false
                        cmd = "ARM_ROT 0"
                    }
                }
                else {
                    if !self.armRotationEngaged {
                        self.armRotationEngaged = true
                        cmd = "ARM_ROT " + (dpad_left > 0 ? "1" : "-1")
                    }
                }

                if dpad_up == 0.0 && dpad_down  == 0.0 {
                    if self.armLiftEngaged {
                        self.armLiftEngaged = false
                        cmd = "ARM_LIFT 0"
                    }
                }
                else {
                    if !self.armLiftEngaged {
                        self.armLiftEngaged = true
                        cmd = "ARM_LIFT " + (dpad_up > 0 ? "1" : "-1")
                    }
                }

                if (l2 == 0.0 && r2 == 0.0)
                {
                    if self.armGripEngaged {
                        self.armGripEngaged = false
                        cmd = "ARM_GRIP 0"
                    }
                }
                else {
                    if !self.armGripEngaged {
                        self.armGripEngaged = true
                        cmd = "ARM_GRIP " + (l2 > 0 ? "1" : "-1")
                    }
                }


                cmd += "\r\n"

                if cmd.characters.count > 3 {
                    print(cmd)
                    self.connMgr.sendCommand(cmd)
                }
            }
        }
        
        NSNotificationCenter.defaultCenter().addObserverForName(GCControllerDidDisconnectNotification, object: nil, queue: nil) { (n) -> Void in
            print("Controller disconnected!")
        }

    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

