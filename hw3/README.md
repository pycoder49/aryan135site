# aryan135site

### ***This README is inside hw3/***

## Team Members (Solo):
1. Aryan Ahuja


github link: https://github.com/pycoder49/aryan135site/tree/main/hw3

## Grader Account
Server IP: 164.92.88.99

**username:** grader<br>
**password:** grader<br>
*Successfully logged in to grader on my local machine*


## Log in for the site:
**username:** aryan<br>
**password:** aryan<br>

## DB: MariaDB
**db name:** analytics135
**username(s):** aryan<br>
**all db passwords:** aryan<br>


## My Domain
https://aryan135.site


## Test site
https://test.aryan135.site


You can see the db /get in action at: https://reporting.aryan135.site/api/events/

My API is api/events/


## What was different in my collector.js

What was done differently:

Compared to the CSE 135 collector tutorial, my collector.js is more behavior-focused and event-driven, rather than the website's modular and framework-style. The tutorial builds a structured collector in stages (hello beacon → technographics → performance timing → web vitals → error tracking → config API), and seems to be introducing named functions like getNavigationTiming(), initPerformanceObserver(), and reportError() as part of a reusable architecture. My implementation is a single self-contained IIFE that directly wires browser APIs to my custom endpoint. I feel like this made my script simpler(?) and more practical for my specific backend, but less modular than the tutorial’s reference-style implementation.

Functionally, I also go beyond the tutorial in some areas while skipping others. I added persistent cid and per-tab sid identity handling, idle detection, throttled interaction tracking (mousemove/scroll), and custom capability probes (imagesEnabled, cssEnabled), which are not emphasized in the tutorial. However, I don’t implement Web Vitals (LCP, CLS, INP), structured performance observers, or a configurable reporting pipeline as shown in modules 6 and 8. My collector is more analytics-product oriented (tracking user behavior and sessions), whereas the tutorial collector is more standards-driven and modular, focusing on browser metrics, structured reporting, and extensibility.
