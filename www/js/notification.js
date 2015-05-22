/**
 * Notification functions.
 */

/**
 * Play notification, if audio-element is present.
 */
function notify()
{
    var notifySound = $("#notify-sound");
    if(notifySound.length > 0) {
        notifySound.get(0).volume = 0.5;
        notifySound.get(0).play();
    }
}

$(function() {
    // Play notification
    notify();
});
