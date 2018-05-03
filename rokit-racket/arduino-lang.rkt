#lang racket

(provide (rename-out [define-user-function define]
                     [my-set! set!]
                     [my-cond cond]
                     [my-begin begin])
         upload
         repeat
         (all-from-out "./arduino-compile.rkt"))

(require "./arduino-compile.rkt")

(require (for-syntax racket))
(require (for-syntax racket/syntax))

(define program '())
(define (set-program! p)
  (set! program p))

(define (upload)
 (send-to-arduino (cons 'begin program)))

(define (cons-end thing l)
  (reverse (cons thing (reverse l))))


(define (mult-list times l)
  (apply append
         (for/list ([i times])
           l)))


(define-syntax (define-identifier stx)
  (syntax-case stx ()
    [(_ name)
     (with-syntax ()
       #`(begin
           (provide name)
           (define name 'name)))]
    [(_ names ...)
     (with-syntax ()
       #`(begin
           (define-identifier names)
           ...))]))


(define-syntax (define-function stx)
  (syntax-case stx ()
    [(_ (name params ...) lines ...)
     (with-syntax ([name-s (syntax->datum #'name)])
       #`(begin
           (provide name)
           (define (name params ...)
             `(name ,params ...))

           (define
             fun-def
             `(define (name params ...)
                ,lines ...))))]
    [(_ name val)
     (with-syntax ()
       #`(begin
           (provide name)
           (define name 'name)

           (define
             fun-def
             `(define name 'name))

           fun-def
           ))]))

(define-syntax (define-functions stx)
  (syntax-case stx ()
    [(_ defs ... )
     (with-syntax ([name-s (syntax->datum #'name)])
       #`(begin
           (define-function defs)
           ...
           ))]))

(define-syntax (define-user-function stx)
  (syntax-case stx ()
    [(_ (name params ...) lines ...)
     (with-syntax ([name-s (syntax->datum #'name)])
       #`(begin
           
           (define (name params ...)
             `(name ,params ...))

           (define
             fun-def
             `(define (name params ...)
                ,lines ...))

           (set-program! (cons-end fun-def program ))
           
           fun-def
           ))]
    [(_ name val)
     (with-syntax (#;[short-name (format-id stx "~a"
                                            (let* ([name-s (~a (syntax->datum #'name)) ])
                                              (if  (string-contains? name-s ":")
                                                   (second (string-split name-s ":"))
                                                   name-s)))])
       #`(begin
           (define name 'name)

           (define
             fun-def
             `(define name val))

           (set-program! (cons-end fun-def program ))
           
           fun-def ))]))


(define-syntax (py-begin stx)
  (syntax-case stx ()
    [(_ lines ...)
     (with-syntax ()
       #`(quasiquote (do
                       ,lines ...)))]))


(define-syntax-rule (define-op local-name real-name)
  (begin
    (provide (rename-out [local-name real-name]))
    (define (local-name . args)
      `(real-name ,@args ))))

(define-op py-gt >)
(define-op py-lt <)
(define-op py-lte <=)
(define-op py-gte >=)
(define-op py-eq  =)
(define-op py-add +)
(define-op py-sub -)
(define-op py-mul *)
(define-op py-div /)
(define-op py-mod %)

(define-identifier
  forward
  backward
  left
  right
  stop
  M1 M2 M3 M4  ;Motors
  CW CCW       ;Motor directions (clockwise ...)
  INPUT OUTPUT ;io directions
  LOW HIGH     ;digital read vals
  )

(define-functions
  (SmartInventor.DCMotor motor-number direction speed)
  (SmartInventor.DCMotorUse)
  (SmartInventor.DCMove direction speed)
  (delay milliseconds)
  (analogRead pin-number)
  (digitalRead pin-number)
  (pinMode pin-number io-direction))

(define (my-set! var-name value)
  `(set! ,var-name ,value))



(define-syntax (my-cond stx)
  (syntax-case stx ()
    [(_ (conds effects) ...)
     (with-syntax ()
       #`(quasiquote (cond
                       (conds ,effects) ...)))]))


(define-syntax (my-begin stx)
  (syntax-case stx ()
    [(_ lines ...)
     (with-syntax ()
       #`(quasiquote (begin
                       ,lines ...)))]))


;A simple "loop" that just unrolls itself at compile time.
(define (repeat times . lines)
  `(begin ,@(mult-list times lines)))





