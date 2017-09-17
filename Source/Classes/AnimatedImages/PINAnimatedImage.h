//
//  PINAnimatedImage.h
//  PINRemoteImage
//
//  Created by Garrett Moon on 9/17/17.
//  Copyright © 2017 Pinterest. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

extern NSString *kPINAnimatedImageErrorDomain;

/**
 PINAnimatedImage decoding and processing errors.
 */
typedef NS_ENUM(NSUInteger, PINAnimatedImageError) {
    /** No error, yay! */
    PINAnimatedImageErrorNoError = 0,
    /** Could not create a necessary file. */
    PINAnimatedImageErrorFileCreationError,
    /** Could not get a file handle to the necessary file. */
    PINAnimatedImageErrorFileHandleError,
    /** Could not decode the image. */
    PINAnimatedImageErrorImageFrameError,
    /** Could not memory map the file. */
    PINAnimatedImageErrorMappingError,
    /** File write error */
    PINAnimatedImageErrorFileWrite,
};

/**
 The processing status of the animated image.
 */
typedef NS_ENUM(NSUInteger, PINAnimatedImageStatus) {
    /** No work has been done. */
    PINAnimatedImageStatusUnprocessed = 0,
    /** Info about the animated image and the cover image are available. */
    PINAnimatedImageStatusInfoProcessed,
    /** At least one set of frames has been decoded to a file. It's safe to start playback. */
    PINAnimatedImageStatusFirstFileProcessed,
    /** The entire animated image has been processed. */
    PINAnimatedImageStatusProcessed,
    /** Processing was canceled. */
    PINAnimatedImageStatusCanceled,
    /** There was an error in processing. */
    PINAnimatedImageStatusError,
};

extern const Float32 kPINAnimatedImageDefaultDuration;
extern const Float32 kPINAnimatedImageMinimumDuration;
extern const NSTimeInterval kPINAnimatedImageDisplayRefreshRate;

@protocol PINAnimatedImage;

@interface PINAnimatedImage : NSObject

/**
 @abstract Return the duration at a given index.
 
 @warning *Must be overridden by subclass
 */
- (CFTimeInterval)durationAtIndex:(NSUInteger)index;

/**
 @abstract Return the total number of frames in the animated image.
 
 @warning *Must be overridden by subclass
 */
@property (nonatomic, readonly) size_t frameCount;

/**
 The number of frames to play per second * display refresh rate (defined as 60 which appears to be true on iOS). You probably want to
 set this value on a displayLink.
 @warning Access to this property before status == PINAnimatedImageStatusInfoProcessed is undefined.
 */
@property (nonatomic, readonly) NSUInteger frameInterval;

@end

@protocol PINAnimatedImage

/**
 @abstract Return the total duration of the animated image's playback.
 */
@property (nonatomic, readonly) CFTimeInterval totalDuration;
/**
 @abstract Return the interval at which playback should occur. Will be set to a CADisplayLink's frame interval.
 */
@property (nonatomic, readonly) NSUInteger frameInterval;
/**
 @abstract Return the total number of loops the animated image should play or 0 to loop infinitely.
 */
@property (nonatomic, readonly) size_t loopCount;
/**
 @abstract Return the total number of frames in the animated image.
 */
@property (nonatomic, readonly) size_t frameCount;
/**
 @abstract Return any error that has occured. Playback will be paused if this returns non-nil.
 */
@property (nonatomic, readonly) NSError *error;

/**
 @abstract Return the image at a given index.
 */
- (CGImageRef)imageAtIndex:(NSUInteger)index;
/**
 @abstract Return the duration at a given index.
 */
- (CFTimeInterval)durationAtIndex:(NSUInteger)index;

@end
