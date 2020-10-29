use employees;

SELECT dept_name FROM departments
WHERE dept_no IN (SELECT dept_no FROM dept_emp
					WHERE emp_no IN (SELECT emp_no FROM employees
									WHERE birth_date = (SELECT MAX(birth_date) FROM employees)));