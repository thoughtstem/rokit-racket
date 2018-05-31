#lang racket

(provide (rename-out [define-user-function define]
                     [my-set! set!]
                     [my-cond cond]
                     [my-begin begin]
                     [my-if if]
                     [my-while while])
         upload
         repeat
         turn
         stop-motors
         (all-from-out "./arduino-compile.rkt"))

(require "./arduino-compile.rkt")

(require (for-syntax racket))
(require (for-syntax racket/syntax))

(define program '())
(define (set-program! p)
  (set! program p))

(define (upload)
 (send-to-arduino (check-program
                   (cons 'begin program))))

(define (check-program p)
  ;(displayln p)
  (ensure-loop (ensure-setup p)))

(define (function->name f)
  (first (second f)))

(define (is-function? l)
  (and (list? l)
       (>= (length l) 2)
       (eq? 'define (first l))
       (list? (second l))))

(define (find-functions p)
  (filter is-function? p))

(define (has-function? name)
  (λ(p)
    (member name (map function->name (find-functions p)))))

(define (check-loop p)
  (displayln "CHECKING FOR LOOP")
    (if ((has-function? 'loop) p)
        (displayln "LOOP FOUND")
        (displayln "NO LOOP")))

(define (check-setup p)
  (displayln "CHECKING FOR SEUTP")
    (if ((has-function? 'setup) p)
        (displayln "SETUP FOUND")
        (displayln "NO SETUP")))

(define (ensure p pred? error-msg)
  (and (not (pred? p))
       (raise error-msg)))

(define (ensure-loop p)
  (check-loop p)
  (if ((has-function? 'loop) p)
      p
      (begin (displayln "ADDING LOOP")
             (append p '((define (loop) )))
             )))

(define (ensure-setup p)
  (check-setup p)
  (if ((has-function? 'setup) p)
      (ensure-motors p)
      (begin (displayln "ADDING SETUP")
             (append p `((define (setup) ,(enable-motors) )))
             )))

(define (function->header f)
  (second f))

(define (function->body f)
  (drop f 2))

(define (add-line-to-function f line)
  `(define
     ,(function->header f)
     ,@(cons line (function->body f))
     ))

(define (add-line-to-function-named f-name line)
  (lambda (program-part)
    (if (or (not (is-function? program-part))
            (not (eq? (function->name program-part) f-name)))
        program-part
        (add-line-to-function program-part line))
    ))

(module+ test
  (define example-program
    '(begin (define (setup)
              (SmartInventor.DCMove forward 60)
              (delay 2000)
              (SmartInventor.DCMove right 60)
              (delay 800)
              (SmartInventor.DCMove forward 60)
              (delay 2000)
              (SmartInventor.DCMove stop 0))

            (define (loop)
              (println "hello world"))))

  (map (add-line-to-function-named 'setup
                                   (enable-motors))
       example-program)
  )

(define (ensure-motors p)
  (map (add-line-to-function-named 'setup
                                   (enable-motors))
       p))
       
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
    [(_ (name alias params ...))
     (with-syntax ([name-s (syntax->datum #'name)])
       #`(begin
           (provide alias)
           (define (alias params ...)
             `(name ,params ...))


           (provide name)
           (define (name params ...)
             `(name ,params ...))

           ))]
    [(_ name alias val)
     (with-syntax ()
       #`(begin
           (provide alias)
           (define alias 'name)

           (provide name)
           (define name 'name)
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

(define-op py-and and)
(define-op py-or or)

(define-identifier
  ;Bot directions
  forward
  backward
  left
  right
  stop
  loose
  
  M1 M2 M3 M4         ;Motors
  CW CCW STOP LOOSE   ;Motor directions (clockwise ...)
  INPUT OUTPUT        ;io directions
  LOW HIGH            ;digital read vals

  NOTE_C2
  NOTE_CS2
  NOTE_D2
  NOTE_DS2
  NOTE_E2
  NOTE_F2
  NOTE_FS2
  NOTE_G2
  NOTE_GS2
  NOTE_A2
  NOTE_AS2
  NOTE_B2
  NOTE_C3
  NOTE_CS3
  NOTE_D3
  NOTE_DS3
  NOTE_E3
  NOTE_F3
  NOTE_FS3
  NOTE_G3
  NOTE_GS3
  NOTE_A3
  NOTE_AS3
  NOTE_B3
  NOTE_C4
  NOTE_CS4
  NOTE_D4
  NOTE_DS4
  NOTE_E4
  NOTE_F4
  NOTE_FS4
  NOTE_G4
  NOTE_GS4
  NOTE_A4
  NOTE_AS4
  NOTE_B4
  NOTE_C5
  NOTE_CS5
  NOTE_D5
  NOTE_DS5
  NOTE_E5
  NOTE_F5
  NOTE_FS5
  NOTE_G5
  NOTE_GS5
  NOTE_A5
  NOTE_AS5
  NOTE_B5
  NOTE_C6
  NOTE_CS6
  NOTE_D6
  NOTE_DS6
  NOTE_E6
  NOTE_F6
  NOTE_FS6
  NOTE_G6
  NOTE_GS6
  NOTE_A6
  NOTE_AS6
  NOTE_B6
  NOTE_C7
  NOTE_CS7
  NOTE_D7
  NOTE_DS7
  NOTE_E7
  NOTE_F7
  NOTE_FS7
  NOTE_G7
  NOTE_GS7
  NOTE_A7
  NOTE_AS7
  NOTE_B7

  KEY_U
  KEY_D
  KEY_L
  KEY_R
  KEY_C
  KEY_F1
  KEY_F2
  KEY_F3
  KEY_F4)

(define-functions
  (SmartInventor.DCMotor       motor
                               motor-number direction speed)
  
  (SmartInventor.DCMotorUse    enable-motors)
  (SmartInventor.TVRemoconUse  enable-remote)
  
  (SmartInventor.TVRemoconData read-remote)
  
  (SmartInventor.DCMove        move
                               direction speed)
  
  (delay                       _delay
                               milliseconds)
  
  (analogRead                  analog-read
                               pin-number)
  
  (digitalRead                 digital-read
                               pin-number)
  
  (digitalWrite                digital-write
                               pin-number high-or-low)
  
  (pinMode                     pin-mode
                               pin-number io-direction)
  
  (SmartInventor.Buzz          buzz
                               note timing))


(define (my-set! var-name value)
  `(set! ,var-name ,value))



(define-syntax (my-cond stx)
  (syntax-case stx (else)
    [(_ (conds effects) ... (else effect))
     (with-syntax ()
       #`(quasiquote (cond
                       (,conds ,effects) ...
                       (else ,effect))))]
    [(_ (conds effects) ... )
     (with-syntax ()
       #`(quasiquote (cond
                       (,conds ,effects) ...)))]))

(define (my-if c t (f 0))
  `(if ,c ,t ,f))


(define (my-while c . lines)
  `(while ,c (begin
               ,@lines)))

;Does this need to be a macro???  If and while are functions...
(define-syntax (my-begin stx)
  (syntax-case stx ()
    [(_ lines ...)
     (with-syntax ()
       #`(quasiquote (begin
                       ,lines ...)))]))


;A simple "loop" that just unrolls itself at compile time.
(define (repeat times . lines)
  `(begin ,@(mult-list times lines)))

(define (turn direction speed)
  (move direction speed))

(define (stop-motors)
  (move stop 0))



