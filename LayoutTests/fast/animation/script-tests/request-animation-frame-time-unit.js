description("Tests time unit of requestAnimationFrame callback");

var isTimeUnitInMs = false;

window.requestAnimationFrame(function(time) {
    var callbackTimeRef = time;
    var timeRefInMs = Date.now();

    setTimeout(function() {
        window.requestAnimationFrame(function(time) {
            var delta = time - callbackTimeRef;
            var deltaTimeInMs = Date.now() - timeRefInMs;
            var toleranceInMs = 10;
            isTimeUnitInMs = Math.abs(delta - deltaTimeInMs) <= toleranceInMs;
            shouldBeTrue("isTimeUnitInMs");
            isSuccessfullyParsed();

            if (window.testRunner)
                testRunner.notifyDone();
        });

        if (window.testRunner)
            testRunner.displayAndTrackRepaints();
    }, 1);
});

if (window.testRunner)
    testRunner.displayAndTrackRepaints();

if (window.testRunner)
    testRunner.waitUntilDone();
