//
// BCOVSSAIComponent.h
// BrightcoveSSAI
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BrightcovePlayerSDK.h>


NS_ASSUME_NONNULL_BEGIN

/**
 * Category methods added to BCOVPlayerSDKManager to support BCOVSSAI.
 */
@interface BCOVPlayerSDKManager (BCOVSSAIAdditions)

/**
 * Creates and returns a new playback controller.
 * The returned playback controller will be configured with a
 * BCOVSSAI session provider.
 *
 * @return A new playback controller with the specified parameters.
 */
- (id<BCOVPlaybackController>)createSSAIPlaybackController;

/**
 * Creates and returns a new SSAI playback controller with the specified view
 * strategy. The returned playback controller will be configured with a
 * BCOVSSAI session provider.
 *
 * @param strategy A view strategy that determines the view for the returned
 * playback controller.
 * @return A new playback controller with the specified parameters.
 */
- (id<BCOVPlaybackController>)createSSAIPlaybackControllerWithViewStrategy:(nullable BCOVPlaybackControllerViewStrategy)strategy;

/**
 * Creates and returns a new BCOVSSAI session provider with the specified
 * parameters.
 *
 * @param provider Optional upstream session provider.
 * @return A new BCOVSSAISessionProvider with the specified parameters.
 */
- (id<BCOVPlaybackSessionProvider>)createSSAISessionProviderWithUpstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider;

#if !TARGET_OS_TV && !TARGET_OS_MACCATALYST
/**
 * Creates and returns a new BCOVSSAI session provider with the specified
 * parameters.
 *
 * @param omidPartnerName Unique partner name given by the IAB Tech Lab for the integration.
 * @param provider Optional upstream session provider.
 * @return A new BCOVSSAISessionProvider with the specified parameters.
 */
- (id<BCOVPlaybackSessionProvider>)createSSAISessionProviderWithUpstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider omidPartner:(NSString *)omidPartnerName;
#endif

@end


/**
 * SSAI specific methods for the plugin context.
 */
@interface BCOVSessionProviderExtension (BCOVSSAIAdditions)

/**
 * The value of this property indicates whether the receiver will ignore `ssai_seekToTime:completionHandler:`
 * or not. The value is NO when either an ad is in progress or the receiver 
 * is still processing a previous messaging of `ssai_seekToTime:completionHandler:`;
 * otherwise, the value of this property is YES. See also `ssai_seekToTime:completionHandler:`.
 */
@property (nonatomic, readonly) BOOL ssai_canSeek;

/**
 * This method implements the default seek behaviour for the BCOVSSAI plugin.
 * This method must be called on the main thread. The receiver will ignore this
 * message when either an ad is in progress or a previous call to `ssai_seekToTime:completionHandler:`
 * is still being processed. See also `ssai_canSeek`.
 *
 * The rules are as follows:
 *
 * - If seeking to end of the logical content time, the post rolls will play.
 * - If seeking over an ad sequence, the ad will play, and the playhead will resume
 * where the seek had attempted to seek to.
 * - If seeking over multiple ad sequences, only the last ad sequence will play.
 * - If seeking backwards, no ads will play.
 * - If seeking over ads that have already been played, they will play again.
 *
 * @param time The logical time to seek to
 * @param completionHandler The block to execute when the seek is performed
 */
- (void)ssai_seekToTime:(CMTime)time completionHandler:(void (^)(BOOL finished))completionHandler;

/**
 * Returns the absolute time that corresponds to the specified content time.
 *
 * This method is used to obtain an absolute stream time that corresponds to
 * a time that is relative to the content. For example, the stream may include
 * a thirty-second ad sequence at `kCMTimeZero`, after which the content begins.
 * In this case, a content time of zero would correspond to an absolute stream
 * time of thirty seconds, and a content time of 2:00 would correspond to an
 * absolute stream time of 2:30 (assuming no other ad sequences occur before
 * that time).
 *
 * @param contentTime A time offset into the video content.
 * @return The absolute time that corresponds to the specified content time.
 */
- (CMTime)ssai_absoluteTimeAtContentTime:(CMTime)contentTime;

/**
 * Returns the content time that corresponds to the specified absolute time.
 *
 * This method is used to obtain a content stream time that corresponds to a
 * time that is relative to the payload. For example, the stream may include
 * a thirty-second ad sequence at 1:30, after which the content begins.
 *
 * In this case, a content time of zero would correspond to an absolute stream
 * time of zero, a content time of 2:00 would correspond to an
 * absolute stream time of 2:30, and a content time of 1:30 would correspond to
 * any absolute stream time from 1:30 to 2:00.
 *
 * @param absoluteTime A time offset into the video payload.
 * @return The content time that corresponds to the specified absolute time.
 */
- (CMTime)ssai_contentTimeAtAbsoluteTime:(CMTime)absoluteTime;

@end

/**
 * Category methods added to BCOVSource to support BCOVSSAI.
 */
@interface BCOVSource (BCOVSSAIAdditions)

/**
 * Constructs a new source with the specified VMAP XML data.
 *
 * @param data The NSData for the new source's VMAP XML configuration
 * @param properties The metadata or properties related to the new source.
 * @return A new source configured with the specified VMAP data.
 */
- (instancetype)initWithVMAPXMLData:(NSData *)data properties:(NSDictionary *)properties;

@end

NS_ASSUME_NONNULL_END
