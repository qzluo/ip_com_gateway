function selFunc(source)
{
	var title = source.getAttribute("title");
	var target = document.getElementById("opraption");
	target.firstChild.nodeValue = title;	
}