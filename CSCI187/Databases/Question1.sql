use employees;
SELECT first_name, last_name FROM employees
WHERE hire_date = (SELECT MIN(hire_date) FROM employees);