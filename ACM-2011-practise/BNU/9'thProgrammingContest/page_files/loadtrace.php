var jkb_id = '2455';
var jkb_url = 'http://acm.bnu.edu.cn/10k.jpg';
var jkb_style = '1';

var jkb_data = [];
var max = 3;
if (jkb_style == '')
{
	jkb_style = '1';
}

var cookies = document.cookie;
if (cookies.indexOf("_jkb_" + jkb_id + "=1") == -1)
{
	trace_init();
}

function trace_init()
{
	if(window.addEventListener)
	{
		window.addEventListener('load', function(){loader(0);}, false);
	}
	else
	{
		window.attachEvent('onload', function(){loader(0);});
	}
}

function loader(times)
{
	if (times > max)
	{	
	
	post();
	
		return;
	}
	var img_url = jkb_url + "?cache=" + Math.floor(100000*Math.random());
	var date = new Date();
	var start = date.getTime();
	var img = document.createElement("img");
	img.style.display = 'none';
	img.style.height = '0';
	img.style.width = '0';
	img.src = img_url;
	img.onload = function()
	{
		if (jkb_data[times])
			return;
		date = new Date();
		var end = date.getTime();
		var diff = end - start;
		jkb_data[times] = diff;
		loader(times + 1);
	};
	document.body.appendChild(img);
}
function post()
{
	var d = [];
	var s = 0;
	var len = jkb_data.length;
	for (i = 0; i < len; ++i)
	{
		var o = 0;
		for (j = 0; j < len; ++j)
		{
			if (j != i)
				o += jkb_data[j];
		}
		if (jkb_data[i] != 0 && jkb_data[i] < o * 2)
		{
			d.push(jkb_data[i]);
			s += jkb_data[i];
		}
	}
	if (d.length == 0)
	{
		return
	}
	var lt = s / d.length;

	var img = document.createElement("img");
	img.style.display = 'none';
	img.style.height = '0';
	img.style.width = '0';
	img.src = 'http://stat.jiankongbao.com:81/loadtime.php?id=' + jkb_id + '&js=1&ref=' + encodeURIComponent(document.referrer) + '&loc=' + encodeURIComponent(window.location.href) + '&lt=' + lt;
	document.body.appendChild(img);
	var expire = new Date();
	expire.setTime(expire.getTime() + 3600 * 1000);
	document.cookie = "_jkb_" + jkb_id + "=1;expires=" + expire.toGMTString();
}
if (jkb_style == '5')
{
	var jkb_dis = '<span style="font-size:12px;">跟踪访问速度</span>';
}
else if (jkb_style == '6')
{
	var jkb_dis = '';
}
else
{
	var jkb_dis = '<img src="http://exp.jiankongbao.com/loadtrace_logo' + jkb_style + '.gif" style="border:0;">';
}
if (jkb_dis != '')
{
	document.write('<a href="http://exp.jiankongbao.com/load.php?host_id=' + jkb_id + '" target="_blank">' + jkb_dis + '</a>');
}

