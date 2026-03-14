# GRADER.md

## Deployment Links

Main class site:

http://aryan135.site

Reporting dashboard:

http://reporting.aryan135.site

------------------------------------------------------------------------

# Login Credentials

## Super Admin

Username: aryan\
Password: aryan

Capabilities:

-   manage users
-   view all reports
-   create and delete users
-   access all report sections

------------------------------------------------------------------------

## Analyst

Username: analyst\
Password: analyst

Capabilities:

-   view assigned report sections
-   create reports
-   save reports
-   write analyst comments

------------------------------------------------------------------------

## Viewer

Username: viewer\
Password: viewer

Capabilities:

-   view saved reports only

------------------------------------------------------------------------

# Suggested Grading Scenario

### Step 1 -- Login as Super Admin

Login using the super admin credentials.

Verify that the dashboard shows: - links to reports - manage users -
saved reports

------------------------------------------------------------------------

### Step 2 -- Manage Users

Navigate to **Manage Users**.

Test: - creating a new user - assigning analyst sections - deleting a
user

------------------------------------------------------------------------

### Step 3 -- Generate a Report

Navigate to **Reports** and select a section such as **Traffic Report**.

Verify: - events table loads - chart visualization appears

------------------------------------------------------------------------

### Step 4 -- Save a Report

Scroll to the **Save Report** section.

Enter: - a report title - analyst comment

Click **Save Report**.

------------------------------------------------------------------------

### Step 5 -- View Saved Reports

Navigate to **Saved Reports**.

Verify that the saved report appears and can be opened.

------------------------------------------------------------------------

### Step 6 -- Test Role Restrictions

Logout and log in as **Analyst**.

Verify: - only assigned sections appear - reports can be created but
users cannot be managed

Logout and log in as **Viewer**.

Verify: - only saved reports can be accessed

------------------------------------------------------------------------

# Known Limitations

### JSON Storage

User data and reports are stored in JSON files instead of a database.
This works for the assignment but would not scale to large production
systems.

### Password Security

Passwords are currently stored without hashing. A production system
would use password hashing (bcrypt) and stronger authentication methods.

### Concurrency

Because reports are stored in JSON files, simultaneous writes could
theoretically cause conflicts if multiple analysts saved reports at the
same time.

------------------------------------------------------------------------

# Areas of Concern

-   race conditions with JSON writes
-   lack of password hashing
-   minimal input validation
-   simple role enforcement logic

These were tradeoffs made to focus on demonstrating the core reporting
functionality for the assignment.
