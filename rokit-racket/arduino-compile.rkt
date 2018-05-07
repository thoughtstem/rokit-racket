#lang racket

(provide send-to-arduino
         set-package-path!)

(require racket-to/processing
         setup/dirs)

(define arduino-executable 
  (match (system-type 'os)
    ('macosx    "/Applications/Arduino.app/Contents/MacOS/Arduino")
    ('unix      "arduino")
    ('windows   "arduino")))

(define (default-package-path)
  (string-append
   (path->string (find-user-pkgs-dir))
   "/rokit-racket/"))

(define package-path   (default-package-path))

(define (set-package-path! s)   (set! package-path s))

;A HACK JUST FOR ME WHILE BUILDING THINGS...
(define (stephens-dev-box?)
  (directory-exists? "/Users/thoughtstem/Dev/"))

;TWIDDLE THE PATHS ON MY COMPUTER. DO NOTHING FOR EVERYONE ELSE
(and (stephens-dev-box?)
     (set-package-path! "/Users/thoughtstem/Dev/RokitRacket/rokit-racket/"))


(define (send-to-arduino code)
  (define compiled-s
    (string-append
     "#include <SmartInventor.h>\n\n" ;Figure imports out automatically based on code??
     (processing-str code)))

  (displayln compiled-s)

  (make-directory* "demo")
  (with-output-to-file "demo/demo.ino" #:exists 'replace
    (lambda () (printf compiled-s)))

  ;TODO: Make this cross platform!!!
  (system (string-append
           "cp -r "
           package-path
           "rokitarduinov1-0-9/* demo/"))

  ;This too!!!
  (system (string-append
           arduino-executable
           " --upload --preferences-file "
           package-path
           "rokitprefs.txt"
           " ./demo/demo.ino")))



 