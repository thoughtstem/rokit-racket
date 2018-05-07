#lang rokit-racket

(define (setup)
  (enable-motors)

  (pin-mode 13 OUTPUT)
  (pin-mode 14 OUTPUT)
  (pin-mode 15 OUTPUT)
  (pin-mode 16 OUTPUT)
  (enable-remote)
  
  (digital-write 13 HIGH)
  (digital-write 14 HIGH)
  (digital-write 15 HIGH)
  (digital-write 16 HIGH))

(define (loop))
