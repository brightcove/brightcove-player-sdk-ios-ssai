//
// BCOVSSAIAdComponentDisplayContainer.h
// BrightcoveSSAI
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVPlaybackController.h>

@class BCOVAd;
@protocol BCOVSSAIAdComponentDelegate;


NS_ASSUME_NONNULL_BEGIN

/**
 * This class is used to display the ad UI and handle companion ads for BCOVSSAI.
 *
 * The UI includes a banner displaying the countdown until content starts and the learn more button
 * and a skip button for skippable ads. This object only added the ad view to the hierarchy
 * when an ad is going to be played, and it is removed when the ad is complete.
 *
 * When an ad contains companions, this object will attempt to match the width
 * and height of those companions with the width and height of the BCOVSSAICompanionSlots
 * managed by this object. If no match is found, the companion will not be populated.
 * If a match occurs, the companion slot will remain populated until another ad
 * with a matching companion slot takes its place.
 *
 * After creating this object, it must be added to the playback controller as a session
 * consumer via `-[BCOVPlaybackController addSessionConsumer:]`.
 */
@interface BCOVSSAIAdComponentDisplayContainer : NSObject <BCOVPlaybackSessionConsumer>

/**
 * The designated initializer.
 *
 * @param companionSlots An array of BCOVSSAICompanionSlots to be populated.
 * @return An initialized instance.
 */
- (nullable instancetype)initWithCompanionSlots:(NSArray *)companionSlots NS_DESIGNATED_INITIALIZER;

/**
 * The delegate for the BCOVSSAIAdComponentDisplayContainer.
 */
@property (nullable, nonatomic, weak) id<BCOVSSAIAdComponentDelegate> delegate;

@end


/**
 * A delegate for BCOVSSAIAdComponentDisplayContainer.
 */
@protocol BCOVSSAIAdComponentDelegate <NSObject>

@optional

/**
 * This delegate method will be called when the learn more button has
 * been pressed and the clickthrough URL assosiated with the ad will be opened 
 * in the in-app browser.
 *
 * @param ad The ad whose clickthrough URL will open in the in-app browser.
 */
- (void)willOpenInAppBrowserWithAd:(BCOVAd *)ad;

/**
 * This delegate method will be called when the learn more button has
 * been pressed and the clickthrough URL assosiated with the ad opened
 * in the in-app browser.
 *
 * @param ad The ad whose clickthrough URL opened in the in-app browser.
 */
- (void)didOpenInAppBrowserWithAd:(BCOVAd *)ad;

/**
 * This delegate method will be called when the in-app browser
 * will be closed.
 *
 * @param ad The ad whose clickthrough URL will close in the in-app browser.
 */
- (void)willCloseInAppBrowserWithAd:(BCOVAd *)ad;

/**
 * This delegate method will be called when the in-app browser
 * has closed.
 *
 * @param ad The ad whose clickthrough URL closed from the in-app browser.
 */
- (void)didCloseInAppBrowserWithAd:(BCOVAd *)ad;

/**
 * This optional delegate method will be called when the the in-app browser
 * will open the clickthrough url in the system browser.
 *
 * @param ad The ad whose clickthrough URL will be opened in the system browser.
 */
- (void)willOpenExternalBrowserWithAd:(BCOVAd *)ad;

@end

NS_ASSUME_NONNULL_END
