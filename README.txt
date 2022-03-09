Challenge
================================

When I search for a keyword in a views combined search box of title and body fields, I would like content that has some other associated keywords to appear in the results.

Requirements
------------

- A Drupal content type called 'Session'.
- A Drupal view of sessions with a combined search box for title and body fields.


Approach
------------

- Create an admin form where associated keywords can be entered.
- Alter the views query to bring up results for the associated keywords as well.
