var dataArray = new Array();
var g_currentDataId = -1;

/*
object {name: 1, 
srcIp: "192.168.1.150", 
tarType: "tcp", 
tarIp: "192.168.1.150",
tarPort: 5678,
srcData: "0x01 0x02 0x03 0x04 0x05 0x06",
tarData: "0x01 0x02 0x03 0x04 0x05 0x06"}
*/

function clearData()
{
	while (dataArray.length > 0)
		dataArray.shift();
}

function testArray()
{
	clearData();
	alert("data length : " + dataArray.length);
	for (var i = 0; i < 10; i++)
	{
		var objData = {name: 1, 
			srcIp: "192.168.1.150", 
			tarType: "tcp", 
			tarIp: "192.168.1.150",
			tarPort: 5678,
			srcData: "0x01 0x02 0x03 0x04 0x05 0x06",
			tarData: "0x01 0x02 0x03 0x04 0x05 0x06"};
		objData.name = i;
		dataArray[i] = objData;
	}

	for (var i = 0; i < 10; i++)
	{
		var objData = {name: 1, 
			srcIp: "192.168.1.150", 
			tarType: "tcp", 
			tarIp: "192.168.1.150",
			tarPort: 5678,
			srcData: "0x01 0x02 0x03 0x04 0x05 0x06",
			tarData: "0x01 0x02 0x03 0x04 0x05 0x06"};
		objData.name = i;
	}
}

function dataManage_loadEvent()
{
	readTermioParas();
}

function readTermioParas()
{
	if (!document.getElementsByTagName)
		return false;

	if (!document.getElementById)
		return false;

	//请求
	var xmlhttp = getHttp();
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
			var rsp = xmlhttp.responseXML;

			//解析 xml 数据，并保存到 dataArray
			updateData(rsp);

			//更新界面
			updateUIData();
		}
	}

	xmlhttp.open("GET","readDataTrans.xml", true);

	
    //xmlhttp.open("GET","termioParas.xml", true);
	//xmlhttp.open("GET","/cgi-bin/readDataTrans.cgi", true);
	xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded"); 
	xmlhttp.send();

	return true;
}

/*更新数据*/
function updateData(xmlRsp)
{
	if (!document.getElementsByTagName)
		return false;

	clearData();
	
	var dataNodes = xmlRsp.documentElement.getElementsByTagName("data");
	if (!dataNodes || dataNodes.length == 0)
		return false;

    for (var i = 0; i < dataNodes.length; i++) {
		var objData = {name: 1, 
			srcIp: "192.168.1.150", 
			tarType: "tcp", 
			tarIp: "192.168.1.150",
			tarPort: 5678,
			srcData: "0x01 0x02 0x03 0x04 0x05 0x06",
			tarData: "0x01 0x02 0x03 0x04 0x05 0x06"};

		//name
		var name = getNodeText(dataNodes[i], "name", 0);
		if (!name) return false;
		objData.name = name;

		//srcIp
		var srcIp = getNodeText(dataNodes[i], "ip", 0);
		if (!srcIp) return false;
		objData.srcIp = srcIp;

		//tarType
		var tarType = getNodeText(dataNodes[i], "type", 0);
		if (!tarType) return false;
		objData.tarType = tarType;

        if (tarType == "tcp" || tarType == "udp") {
			//tarIp
			var tarIp = getNodeText(dataNodes[i], "ip", 1);
			if (!tarIp) return false;
			objData.tarIp = tarIp;

			//tarPort
			var tarPort = getNodeText(dataNodes[i], "port", 0);
			if (!tarPort) return false;
			objData.tarPort = tarPort;
        }		

		//srcData
		var srcData = getNodeText(dataNodes[i], "srcData", 0);
		if (!srcData) return false;
		objData.srcData = srcData;

		//tarData
		var tarData = getNodeText(dataNodes[i], "tarData", 0);
		if (!tarData) return false;
		objData.tarData = tarData;

		//append child
		dataArray.push(objData);
    }

	return true;
}

/*更新导航树的菜单项*/
function updateUIData()
{
	if (!document.getElementById)
		return false;

	clearUIData();

	if (dataArray.length > 0)
		g_currentDataId = 2;
	else
		g_currentDataId = -1;	

	updateMainUI();

	var tarParent = document.getElementById("datalist");
	if (!tarParent)
		return false;

	for (var i = 0; i < dataArray.length; i++) {
		var liNode = document.createElement("li");
		if (!liNode)
			return false;
		liNode.setAttribute("class", "sublist");

		var textNode = document.createTextNode(dataArray[i].name);
		if (!textNode)
			return false;

		liNode.appendChild(textNode);
		tarParent.appendChild(liNode);
	}

	return true;
}

/*删除导航树的菜单项*/
function clearUIData()
{
	if (!document.getElementsByTagName)
		return false;

	if (!document.getElementById)
		return false;

	var tarParent = document.getElementById("datalist");
	if (!tarParent)
		return false;

	var datalist = tarParent.getElementsByTagName("li");
	while (datalist.length > 0)	
		tarParent.removeChild(datalist[datalist.length - 1]);

	return true;
}

/*更新数据操作界面*/
function updateMainUI()
{
	if (!document.getElementById)
		return false;

	if (g_currentDataId < 0)
		return clearMainUI();

	if (g_currentDataId >= dataArray.length)
		return false;

	var objData = dataArray[g_currentDataId];

	//name
	var nodeSelected = document.getElementById("objName");
	if (!nodeSelected) return false;
	nodeSelected.setAttribute("value", objData.name);

	//src ip
	nodeSelected = document.getElementById("srcIp");
	if (!nodeSelected) return false;
	nodeSelected.setAttribute("value", objData.srcIp);

	//srcData
	nodeSelected = document.getElementById("srcData");
	if (!nodeSelected) return false;
	var textNode = nodeSelected.firstChild;
	if (textNode) 
		textNode.nodeValue = objData.srcData;
	else {
		textNode = document.createTextNode(objData.srcData);
		nodeSelected.appendChild(textNode);
	}

	//tarType
	nodeSelected = document.getElementById("termio");
	if (!nodeSelected) return false;
	for (var i = 0; i < nodeSelected.options.length; i++) {
		if (objData.tarType == nodeSelected.options[i].getAttribute("value"))
			nodeSelected.options[i].setAttribute("selected", "true");
		else
			nodeSelected.options[i].setAttribute("selected", "false");
	}
    
	if (objData.tarType == "tcp" || objData.tarType == "udp") {
		//tarIp
		nodeSelected = document.getElementById("tarIp");
		if (!nodeSelected) return false;
		nodeSelected.setAttribute("value", objData.tarIp);

		//tarPort
		nodeSelected = document.getElementById("tarPort");
		if (!nodeSelected) return false;
		nodeSelected.setAttribute("value", objData.tarPort);
	}
	
    //tarData
	nodeSelected = document.getElementById("tarData");
	if (!nodeSelected) return false;
	textNode = nodeSelected.firstChild;
	if (textNode) 
		textNode.nodeValue = objData.tarData;
	else {
		textNode = document.createTextNode(objData.tarData);
		nodeSelected.appendChild(textNode);
	}

	return true;
}

function clearMainUI()
{
	if (!document.getElementById)
		return false;

	//name
	var nodeSelected = document.getElementById("objName");
	if (!nodeSelected) return false;
	nodeSelected.setAttribute("value", "");
	
	//src ip
	nodeSelected = document.getElementById("srcIp");
	if (!nodeSelected) return false;
	nodeSelected.setAttribute("value", "");

	//srcData
	nodeSelected = document.getElementById("srcData");
	if (!nodeSelected) return false;
	if (nodeSelected.firstChild)
		nodeSelected.firstChild.value = "";

	//tarType
	nodeSelected = document.getElementById("termio");
	if (!nodeSelected) return false;
	nodeSelected.setAttribute("value", "");
    
	//tarType
	nodeSelected = document.getElementById("tarIp");
	if (!nodeSelected) return false;
	nodeSelected.setAttribute("value", "");

	//tarPort
	nodeSelected = document.getElementById("tarPort");
	if (!nodeSelected) return false;
	nodeSelected.setAttribute("value", "");
	
    //srcData
	nodeSelected = document.getElementById("tarData");
	if (!nodeSelected) return false;
	if (nodeSelected.firstChild)
		nodeSelected.firstChild.value = "";

	return true;
}

/*
function setComData(xmlRsp, comName)
{
	if (!document.getElementsByTagName)
		return false;

	if (!document.getElementById)
		return false;

	//com
	var comNodes = xmlRsp.documentElement.getElementsByTagName(comName);
	if (!comNodes || comNodes.length == 0)
		return false;

    //baud
	var bauds = comNodes[0].getElementsByTagName("baud");
	if (!bauds || bauds.length == 0)
		return false;

	var boauText = bauds[0].firstChild.nodeValue;
	var comBaudId = comName + "Baud";
	var comBaud = document.getElementById(comBaudId);
	if (!comBaud)
		return false;

	comBaud.setAttribute("value", boauText);

    //databit
	var databits = comNodes[0].getElementsByTagName("databit");
	if (!databits || databits.length == 0)
		return false;

	var databitText = databits[0].firstChild.nodeValue;
	var comDatabitId = comName + "Databit";
	var comDatabit = document.getElementById(comDatabitId);
	if (!comDatabit)
		return false;

	comDatabit.setAttribute("value", databitText);

    //stopbit
	var stopbits = comNodes[0].getElementsByTagName("stopbit");
	if (!stopbits || stopbits.length == 0)
		return false;

	var stopbitText = stopbits[0].firstChild.nodeValue;
	var comStopbitId = comName + "Stopbit";
	var comStopbit = document.getElementById(comStopbitId);
	if (!comStopbit)
		return false;

	comStopbit.setAttribute("value", stopbitText);

	//validate
	var validatebits = comNodes[0].getElementsByTagName("validatebit");
	if (!validatebits || validatebits.length == 0)
		return false;

	var validateText = validatebits[0].firstChild.nodeValue;
	var comValidatebitId = comName + "Validatebit";
	var comValidatebit = document.getElementById(comValidatebitId);
	if (!comValidatebit)
		return false;

	comValidatebit.setAttribute("value", validateText);
}

function termioUpdate()
{
	if (!document.getElementById)
		return false;

	//请求
	var xmlhttp = getHttp();
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
			var rsp = xmlhttp.responseText;
			alert(rsp);
		}
	}

	//send info
	var strTcpValue;

	var tcpport = document.getElementById("tcpport");
	if (!tcpport)
		return false;

	var portText = tcpport.value;
	strTcpValue = "tcp=" + "tcp:" + portText;

	//com2
	var strCom2Value = getComParaText("com2");
	var strCom3Value = getComParaText("com3");
	var strCom4Value = getComParaText("com4");

	var str = strTcpValue + "&" + strCom2Value + "&" + 
		strCom3Value + "&" + strCom4Value;

	xmlhttp.open("POST","/cgi-bin/writeTermioParas.cgi", true);
	xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded"); 
	xmlhttp.send(str);
}

function getComParaText(comName)
{
	if (!document.getElementById)
		return false;

	//baud
	var comBaudId = comName + "Baud";
	var comBaud = document.getElementById(comBaudId);
	if (!comBaud)
		return false;

	var boauText = comBaud.value;

	//databit
	var comDatabitId = comName + "Databit";
	var comDatabit = document.getElementById(comDatabitId);
	if (!comDatabit)
		return false;

	var databitText = comDatabit.value;

	//stopbit
	var comStopbitId = comName + "Stopbit";
	var comStopbit = document.getElementById(comStopbitId);
	if (!comStopbit)
		return false;

	var stopbitText = comStopbit.value;

	//validatebit
	var comValidatebitId = comName + "Validatebit";
	var comValidatebit = document.getElementById(comValidatebitId);
	if (!comValidatebit)
		return false;

	var validateText = comValidatebit.value;

	var retText;
	retText = comName + "=" + comName + ":" + boauText + ":" 
		+ databitText + ":" + stopbitText + ":" + validateText;

	return retText;
}
*/


function getNodeText(parent, tagName, index)
{
	if (!document.getElementsByTagName)
		return false;

	var nodeList = parent.getElementsByTagName(tagName);
	if (!nodeList || nodeList.length <= index)
		return false;

	return nodeList[index].firstChild.nodeValue;
}

addEvent(dataManage_loadEvent);
