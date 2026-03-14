# aryan135site

### ***This README is inside hw5/***

## Team Members (Solo):
1. Aryan Ahuja


github link: https://github.com/pycoder49/aryan135site/tree/main/hw5

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

## Log in for **reporting.aryan135.site** or **reporting.aryan135.site/index.php**
**username 1:** aryan<br>
**password 1:** aryan<br>

**username 2:** grader<br>
**password 2:** grader<br>


## My Domain
https://aryan135.site

## Test site (from hw3)
https://test.aryan135.site

## Reporting sites for hw4
https://reporting.aryan135.site/index.php <br>
https://reporting.aryan135.site/login.php <br>
https://reporting.aryan135.site/logout.php <br>
https://reporting.aryan135.site/report.php <br>
https://reporting.aryan135.site/authenticate.php <br>
https://reporting.aryan135.site/auth.php <br>
**MORE WERE ADDED FOR HW5 AND SOME OF THESE WERE CHANGED**


My API is `api/events/`

You can see the db /get in action at: https://reporting.aryan135.site/api/events/
<br> ^^ This is raw data

Actual html table and chart is at: https://reporting.aryan135.site/report.php <br>
**THE CHART TAKES A FEW SECOND TO LOAD -- THANK YOU FOR YOUR PATIENCE**




## H5 Stats

### Role-Based Access Control

The system implements three user roles:

-   **Super Admin**
    -   Full access to all features
    -   Can create and delete users
    -   Can view all reports
    -   Can assign analyst permissions
-   **Analyst**
    -   Can view assigned report sections
    -   Can generate and save reports
    -   Can write analyst comments
-   **Viewer**
    -   Can only view saved reports


### Report Sections

The dashboard includes three report categories:

-   Performance
-   Behavior
-   Traffic

Analysts may only access the sections assigned to them.


### Saved Reports

Saved reports include:

-   Title
-   Section
-   Analyst comment
-   Author
-   Timestamp

Users with appropriate permissions can view saved reports and export them as PDF.


### User Management

Super admins can:

-   Create users
-   Assign roles
-   Assign analyst sections
-   Delete users

User data is stored in `/data/users.json`.


## Use of AI

I did use AI. AI was used for the following:
1. Planning the structure of my droplet, to make sure I wasn't making double files/structures
2. Learning PHP and looking up PHP syntax optimizations since I chose to do everything in PHP
3. To improve my CSS files to make sure everything was uniform
4. Learning the basics for C++/Rust/PHP cgi files for Hw 3
5. To understand how apache2 worked under the hood and to make it all click in my head

Oh and also to structure this specific readme so it would be clear for the graders.


## Future Improvements

If more time were available, the following improvements would be
implemented:

-   Password hashing and stronger authentication security
-   Database storage instead of JSON files
-   Report editing functionality
-   Improved UI/UX styling
-   Pagination for large event datasets
-   Filtering by date range
-   Better error handling and validation -- I just wing some security checks right now in different files