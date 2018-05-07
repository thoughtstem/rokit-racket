#lang rokit-racket

(define (setup)
  (enable-motors))

(define (loop)
  (repeat 2
          (move right 50)
          (delay 1000)))

 