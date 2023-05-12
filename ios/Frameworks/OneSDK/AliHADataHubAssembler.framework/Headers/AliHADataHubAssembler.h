//
//  AliHADataHubImp.h
//  AliHACore
//
//  Created by hansong.lhs on 2018/5/22.
//

#import <Foundation/Foundation.h>

#import <AliAPMInterface/AliAPMInterface.h>
#import <AliHADataHub4iOS/AliHADataHub.h>
#import <AliHAProtocol/AliHAProtocol.h>

#pragma data context lifecycle protocol

@interface AliHADataHubAssembler : NSObject <ProcedureTrackInteface, AliHADataHubSubscriber, AliHAPluginProtocol>

+ (instancetype)sharedInstance;

@end

