/*function lol(){
	var form = document.forms;
	var mas = {};
	for (var l = 0; l < form.length; l++){
		var attr = form[l].getAttribute('name');
		//alert(attr);
		attr = String(attr);
		mas.form[l].getAttribute('name') = 0;
		var elems = form[l].elements.ans;
		for (var i = 0; i < elems.length; i++){
			if (elems[i].checked){
				mas.attr = elems[i].value;
			}
		}
	}
	alert(mas['5'])	
	//Object.keys(mas).forEach(function(key, id) {
    //	alert('id: '+id+', key: '+ key +' = ' + mas[key]);
//});
}
*/
function lol(){
	var form = document.forms;
	var attr = form.getAttribute('name');
	var mas = {};
	for (var l of attr){
		alert(l);
		mas.l = 0;
		var elems = form[l].elements.ans;
		for (var i = 0; i < elems.length; i++){
			if (elems[i].checked){
				mas.attr = elems[i].value;
			}
		}
	}
	alert(mas['5'])	
	//Object.keys(mas).forEach(function(key, id) {
    //	alert('id: '+id+', key: '+ key +' = ' + mas[key]);
//});

}