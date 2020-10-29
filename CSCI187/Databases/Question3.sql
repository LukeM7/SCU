use employees;

SELECT first_name,last_name FROM employees
WHERE emp_no IN (SELECT emp_no FROM dept_manager
				WHERE emp_no IN (SELECT emp_no FROM dept_emp
                WHERE dept_no IN (SELECT dept_no FROM departments
                WHERE dept_no IN (SELECT dept_no FROM dept_emp
                WHERE emp_no IN (SELECT emp_no FROM employees
                WHERE birth_date = (SELECT MIN(birth_date) FROM employees)
                )))));