//
// BrightcoveSSAI.h
// BrightcoveSSAI
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import <BrightcoveSSAI/BCOVSSAIAdComponentDisplayContainer.h>
#import <BrightcoveSSAI/BCOVSSAICompanionSlot.h>
#import <BrightcoveSSAI/BCOVSSAIComponent.h>
#import <BrightcoveSSAI/BCOVSSAIConstants.h>

// Declares BCOVOUXSessionProviderOptions and BCOVSSAINextGenLiveDetection.
// Without this an integrator cannot name either type, so the options object
// -createSSAISessionProviderWithUpstreamSessionProvider:options: takes could
// not be constructed.
#import <BrightcoveSSAI/BCOVSSAISessionProviderOptions.h>
