//
// BCOVSSAISessionProviderOptions.h
// BrightcoveSSAI
//
// Copyright (c) 2026 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//
// Split out of BCOVOUXSessionProvider.h so an integrator can name these types.
// That header is a project-internal header in the framework build, so anything
// declared only there cannot be constructed by an app — which would leave
// -createSSAISessionProviderWithUpstreamSessionProvider:options: impossible to
// call. This header imports nothing but Foundation, so it can be exported
// without also exporting the session provider, which clients are not meant to
// construct directly.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * How a NextGen Live (Cloud Playout 2.0) SSAI source is recognised.
 *
 * NextGen Live streams are stitched by the server and carry no VMAP document,
 * so they take a different path through the session provider than Legacy Live
 * or VOD SSAI. This controls when that path is taken.
 */
typedef NS_ENUM(NSInteger, BCOVSSAINextGenLiveDetection)
{
    /**
     * Do not treat any source as NextGen Live. NextGen Live streams fall
     * through to the existing SSAI handling, which means they play as plain
     * video with no ad features rather than failing.
     *
     * This is the client-side off switch: an app that ships with NextGen Live
     * support can disable it without a new build being required to recover.
     */
    BCOVSSAINextGenLiveDetectionDisabled = 0,

    /**
     * Recognise a source by its host, `ssai.live.brightcove.com`.
     */
    BCOVSSAINextGenLiveDetectionHostname,

    /**
     * Recognise a source by a JWT-shaped `livePlaybackToken` in its properties.
     */
    BCOVSSAINextGenLiveDetectionPlaybackToken,

    /**
     * Recognise a source by either signal. The default.
     */
    BCOVSSAINextGenLiveDetectionEither
};


/**
 * Optional configuration for BCOVOUX session providers.
 *
 * Pass one to
 * `-[BCOVPlayerSDKManager createSSAISessionProviderWithUpstreamSessionProvider:options:]`.
 */
@interface BCOVOUXSessionProviderOptions : NSObject <NSCopying>

#if !TARGET_OS_TV && !TARGET_OS_MACCATALYST
@property (nonatomic, strong) NSString *omidPartnerName;
#endif

/**
 * How NextGen Live (Cloud Playout 2.0) sources are recognised.
 *
 * Defaults to `BCOVSSAINextGenLiveDetectionEither`. Set to
 * `BCOVSSAINextGenLiveDetectionDisabled` to turn NextGen Live handling off;
 * affected streams then play without ad features instead of erroring.
 */
@property (nonatomic, assign) BCOVSSAINextGenLiveDetection nextGenLiveDetection;

/**
 * Custom ad targeting parameters for NextGen Live (Cloud Playout 2.0) SSAI
 * sessions.
 *
 * These are sent in the `adsParams` field of the session initialization POST
 * body. The SSAI server uses them to replace macros in the ad tag URL. Keys and
 * values are both strings.
 *
 * Must be set before the session provider is created to take effect, because
 * session initialization happens as soon as a NextGen Live source is loaded.
 *
 *     BCOVOUXSessionProviderOptions *options = [BCOVOUXSessionProviderOptions new];
 *     options.live2AdsParams = @{ @"deviceType": @"mobile", @"uid": userId };
 *
 * Ignored for Legacy Live and VOD SSAI sources, which carry their ad targeting
 * in the VMAP URL instead.
 */
@property (nonatomic, copy) NSDictionary<NSString *, NSString *> *live2AdsParams;

@end

NS_ASSUME_NONNULL_END
