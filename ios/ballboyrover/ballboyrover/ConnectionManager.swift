//
//  ConnectionManager.swift
//  RobotController-WiFi2Wheel
//
//  Created by Eric Castro on 20/09/15.
//  Copyright © 2015 Eric Castro. All rights reserved.
//

import UIKit

class ConnectionManager: NSObject {

    static let sharedInstance = ConnectionManager()
    
    var asyncSocket:AsyncSocket
    
    override init() {
        
        self.asyncSocket = AsyncSocket()
        
        super.init()
        
        self.asyncSocket.setDelegate(self)
        
        do {
            try self.asyncSocket.connectToHost("192.168.1.90", onPort: 5555)
        }
        catch {
            print("problemo")
        }
        
        
    }
    
    func onSocket(sock: AsyncSocket!, didWriteDataWithTag tag: Int) {
        print("WriteData")
    }
    
    func onSocket(sock: AsyncSocket!, didReadData data: NSData!, withTag tag: Int) {
        if let datastring = NSString(data:data, encoding:NSUTF8StringEncoding) {
        
            //do smething with data received
            
        }
        
        self.asyncSocket.readDataWithTimeout(-1, tag: 0)
    }
    
    func onSocket(sock: AsyncSocket!, didConnectToHost host: String!, port: UInt16) {
        print("Info___didConnectToHost")
        self.asyncSocket.readDataWithTimeout(-1, tag: 0)
    }
    
    func onSocket(sock: AsyncSocket!, willDisconnectWithError err: NSError!) {
        print("Info___willDisconnectWithError")
        print(err)
    }
    
    func sendCommand(command:String) {
        let data = command.dataUsingEncoding(NSUTF8StringEncoding)
        self.asyncSocket.writeData(data, withTimeout: -1, tag: 0)
    }
    
}
