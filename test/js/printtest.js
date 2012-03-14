var show_hide = function(element)
{
	  element.style.display = (element.style.display == "") ? "none" : "";
}

var update_counts = function(counts)
{
	counts.innerHTML = "<div style='color:green'>passed: " + counts.pass_count + "</div><br>" + 
						"<div style='color:red'>failed: " + counts.fail_count + "</div><br>";
}

function print_test(test)
{
	/*
	* Takes a test object like:
	* var test = 	{
	*					Name: 'Challenge #1', 
	*					Parameters: {
	*									private_key: 'key',
	*									public_key: 'key',
	*									seed_string: 'seed',
	*									challenge: 'challenge',
	*									correct_answer: 'correct answer',
	*									given_answer: 'given answer',
	*								},
	*					Status: 'pass or fail',
	*			};
	* 
	* And prints it nicely into the status <div>
	*/
	var outer_container = document.getElementById('status');
	
	var counts = document.getElementById('generalstatus')
	if(!counts)
	{
		counts = document.createElement('div');
		counts.id = 'generalstatus';
		counts.pass_count = 0;
		counts.fail_count = 0;
		
		outer_container.appendChild(counts);
	}
	
	var container = document.getElementById('detailedstatus');
	if(!container)
	{
		container = document.createElement('div');
		container.id = 'detailedstatus';
		
		var toggle_details = document.createElement('div');
		toggle_details.innerHTML = "&rArr;Details";
		toggle_details.style.color = 'blue';
		toggle_details.style.cursor = 'pointer';
		toggle_details.toggled_off = true;
		toggle_details.onclick = function()
		{
			show_hide(container);
			if (toggle_details.toggled_off)
			{
				toggle_details.innerHTML = "&dArr;Details";
				toggle_details.toggled_off = false;
			}
			else
			{
				toggle_details.innerHTML = "&rArr;Details";
				toggle_details.toggled_off = true;
			}
		}
		outer_container.appendChild(toggle_details);
		
		container.style.display = 'none';
		
		outer_container.appendChild(container);
	}
	
	if (container.firstChild) 
	{
		var br = document.createElement('br');
		container.appendChild(br);
	}
	var test_div = document.createElement('div');
	
	var name = document.createElement('h3');
	var txt = document.createTextNode(test.Name);
	name.appendChild(txt);
	test_div.appendChild(name);
	
	var parameter_table = document.createElement('table');
	
	var toggle_params = document.createElement('div');
	toggle_params.innerHTML = "&rArr;Parameters";
	toggle_params.style.color = 'blue';
	toggle_params.style.cursor = 'pointer';
	toggle_params.toggled_off = true;
	toggle_params.onclick = function()
	{
		show_hide(parameter_table);
		if (toggle_params.toggled_off)
		{
			toggle_params.innerHTML = "&dArr;Parameters";
			toggle_params.toggled_off = false;
		}
		else
		{
			toggle_params.innerHTML = "&rArr;Parameters";
			toggle_params.toggled_off = true;
		}
	}
	test_div.appendChild(toggle_params);
	
	parameter_table.style.display = 'none';
	for (parameter_name in test.Parameters)
	{
		var parameter_row = document.createElement('tr');
		
		var parameter_key = document.createElement('td');
		var txt = document.createTextNode(parameter_name);
		parameter_key.appendChild(txt);
		parameter_key.style.border = "1px solid grey";
		parameter_row.appendChild(parameter_key);
		
		var parameter_value = document.createElement('td');
		var txt = document.createTextNode(test.Parameters[parameter_name]);
		parameter_value.appendChild(txt);
		parameter_value.style.border = "1px solid grey";
		parameter_row.appendChild(parameter_value);
		
		parameter_table.appendChild(parameter_row);
	}
	
	test_div.appendChild(parameter_table);
	
	var status = document.createElement('p');
	status.style.fontWeight = "bold";
	var txt = document.createTextNode(test.Status);
	if (test.Status=='pass')
	{
		counts.pass_count += 1;
		status.style.color = 'green';
	}
	else if (test.Status=='fail')
	{
		counts.fail_count += 1;
		status.style.color = 'red';
	}
	update_counts(counts);
	status.appendChild(txt);
	test_div.appendChild(status);
	
	container.appendChild(test_div);
}