#lang scribble/manual
 
@title{#lang rokit-racket}

This language allows you to code the Rokit SmartInventor 2 robotics kit from Robolink (robolink.com).

We use this in robotics classes at ThoughtSTEM.

This doc just contains a bunch of example code.


@section{Basic Movement}

@codeblock|{
#lang rokit-racket

(define (wait) 
  (delay 5000))

(define (setup)
  (enable-motors))

(define (loop)
  (move forward 127)
  (wait)
  (move stop 127)
  (wait)) 
}|



@section{Remote Control}

@codeblock|{
#lang rokit-racket

(define (setup)
  (enable-motors)
  (enable-remote)
  
  (buzz NOTE_C4 8)
  (buzz NOTE_E4 8)
  (buzz NOTE_G4 8))

(define (boost)
  (move forward 127)
  (delay 1000))

(define (spin180)
  (motor M1 CW 127)
  (motor M2 CW 127)
  (delay 650)
  (move stop 0)
  (delay 200))

(define (zig-zag)
  (repeat 2
          (motor M1 CCW 127)
          (motor M2 STOP 0)
          (delay 400)
          (motor M1 STOP 0)
          (motor M2 CW 127)
          (delay 400)))

(define (loop)
  (cond
    [(= (read-remote) KEY_U) 
      (move forward 50)]
    [(= (read-remote) KEY_D) 
      (move backward 50)]
    [(= (read-remote) KEY_L) 
      (move left 50)]
    [(= (read-remote) KEY_R) 
      (move right 50)]
    [(= (read-remote) KEY_C) 
      (boost)]
    [(= (read-remote) KEY_F1) 
      (spin180)]
    [(= (read-remote) KEY_F2) 
      (zig-zag)]
    [else
     (move loose 50)]))

}|

@section{Analog Read}

@codeblock|{
#lang rokit-racket

(define left-sensor 0)
(define center-sensor 0)
(define right-sensor 0)
                    
(define (setup)
  (enable-motors))

(define (loop)
  (set! left-sensor   (analog-read 19))
  (set! center-sensor (analog-read 20))
  (set! right-sensor  (analog-read 21))

  (cond
    [(< left-sensor   500) (move right 50)]
    [(< right-sensor  500) (move left 50)]
    [(< center-sensor 500) (move left 50)]
    [else                 (move forward 50)]))
}|

@section{Digital Write}

@codeblock|{
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
}|


@section{Line follow}

@codeblock|{
#lang rokit-racket
 
(define left-line-sensor #f)
(define right-line-sensor #t)

(define (setup)
  (enable-motors)

  (pin-mode 13 INPUT)
  (pin-mode 16 INPUT))

(define (loop)
  (set! left-line-sensor  (digital-read 13))
  (set! right-line-sensor (digital-read 16))

  (while (= left-line-sensor HIGH)
         (motor M1 CCW 50)
         (motor M2 STOP 0)
         (set! left-line-sensor (digital-read 13)))

  (while (= right-line-sensor HIGH)
         (motor M1 STOP 0)
         (motor M2 CW 50)
         (set! right-line-sensor (digital-read 16))))
}|


@section{Digital Read}

@codeblock|{
#lang rokit-racket
 
(define left-sensor  #f)
(define right-sensor #f)
 
(define (setup)
  (enable-motors)
  (pin-mode 11 INPUT)
  (pin-mode 18 INPUT))

(define (backup-and-turn-right)
  (motor M1 CW 50)
  (motor M2 CCW 50)
  (delay 333)
  (motor M1 CCW 50)
  (motor M2 CCW 50)
  (delay 333))

(define (backup-and-turn-left)
  (motor M1 CW 50)
  (motor M2 CCW 50)
  (delay 333)
  (motor M1 CW 50)
  (motor M2 CW 50)
  (delay 333))

(define (go-forward)
  (motor M1 CCW 50)
  (motor M2 CW 50))
 
(define (loop)
  (set! left-sensor   (digital-read 11)) 
  (set! right-sensor  (digital-read 18)) 
   
  (cond 
    [(= left-sensor   #f) (backup-and-turn-right)]
    [(= right-sensor  #f) (backup-and-turn-left)]
    [else (go-forward)]))
}|

