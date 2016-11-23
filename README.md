# 18650 / LiIon capacity checker

This is based on the work from Adam Welch http://adamwelch.co.uk/2016/01/lithium-ion-18650-battery-capacity-checker/ with several changes

* Ability to discharge 4 cells instead of 1
* Arduino code re-factored to use a [millis() timer](http://playground.arduino.cc/Code/AvoidDelay) rather than delay()
* LCD code removed to maximize available Arduino pins
* Logging is done over serial to a Raspberry Pi
* A script runs on the Raspberry Pi to send a tweet when all cells have been discharged

Features I'm looking to add:

* JSON output
* REST API
* Ability to replace individual cells that are complete

Feel free to submit a pull request.

Thanks.
