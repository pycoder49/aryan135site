# aryan135site

### ***This README is inside hw4/***

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


My API is `api/events/`

You can see the db /get in action at: https://reporting.aryan135.site/api/events/
<br> ^^ This is raw data

Actual html table and chart is at: https://reporting.aryan135.site/report.php


## Step 1: Cutting off backend with login
I migrated `index.html` for reprting domain to `index.php`

You can see you'll need to be authenticated before accessing anything on that domain

In my code, I havae set auth to be required only once per sesison. So if you're logged in, you'll stay logged in even if the page reloads

What truly logs you out is pressing the log out button, that button destroys the session so you'll stay logged out. The 2 logins are provided above

There is no sign up mechanism


## Step 2: Creating a table in HTML to display api results
I made a basic table in HTML with minimal CSS (styling) and JS (fetching the api) that displays the API results.

It also shows only a certain amount of entries, since all the entries would be overwhemling and would require you to scroll a lot (because the chart for step 3 is under the html table)


## Step 3: Creating a Chart
My choice of chart was the Bar plot.

On the X axis, I have the different fields that I'm tracking using the API. <br>And on the Y axis, there are quantifiable numbers.

Given the fetched data (for the table), the chart counts and makes use of them and then displays the result.

The chart was loaded through Chart.js
