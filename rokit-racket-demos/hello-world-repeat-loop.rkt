#lang rokit-racket

(define (setup)
  (SmartInventor.DCMotorUse))

(define (loop)
  (repeat 2
          (SmartInventor.DCMove right 50)
          (delay 1000)))

 