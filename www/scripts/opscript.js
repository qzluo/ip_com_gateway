function selFunc(source)
{
	var title = source.getAttribute("title");
	var target = document.getElementById("opcaption");
	target.firstChild.nodeValue = title;	
}