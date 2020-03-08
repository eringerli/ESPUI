const char JS_CONTROLS[] PROGMEM = R"=====(
const UI_INITIAL_GUI=200;const UI_BATCH_UPDATE=201;const UPDATE_OFFSET=100;const UI_TITEL=0;const UI_PAD=1;const UPDATE_PAD=101;const UI_CPAD=2;const UPDATE_CPAD=102;const UI_BUTTON=3;const UPDATE_BUTTON=103;const UI_LABEL=4;const UPDATE_LABEL=104;const UI_SWITCHER=5;const UPDATE_SWITCHER=105;const UI_SLIDER=6;const UPDATE_SLIDER=106;const UI_NUMBER=7;const UPDATE_NUMBER=107;const UI_TEXT_INPUT=8;const UPDATE_TEXT_INPUT=108;const UI_GRAPH=9;const ADD_GRAPH_POINT=10;const CLEAR_GRAPH=109;const UI_TAB=11;const UPDATE_TAB=111;const UI_SELECT=12;const UPDATE_SELECT=112;const UI_OPTION=13;const UPDATE_OPTION=113;const UI_MIN=14;const UPDATE_MIN=114;const UI_MAX=15;const UPDATE_MAX=115;const UI_STEP=16;const UPDATE_STEP=116;const UP=0;const DOWN=1;const LEFT=2;const RIGHT=3;const CENTER=4;const C_TURQUOISE=0;const C_EMERALD=1;const C_PETERRIVER=2;const C_WETASPHALT=3;const C_SUNFLOWER=4;const C_CARROT=5;const C_ALIZARIN=6;const C_DARK=7;const C_NONE=255;function colorClass(colorId){colorId=Number(colorId);switch(colorId){case C_TURQUOISE:return"turquoise";case C_EMERALD:return"emerald";case C_PETERRIVER:return"peterriver";case C_WETASPHALT:return"wetasphalt";case C_SUNFLOWER:return"sunflower";case C_CARROT:return"carrot";case C_ALIZARIN:return"alizarin";case C_NONE:return"dark";default:return"";}}
var websock;var websockConnected=false;function restart(){$(document).add("*").off();$("#row").html("");websock.close();start();}
function conStatusError(){websockConnected=false;$("#conStatus").removeClass("color-green");$("#conStatus").addClass("color-red");$("#conStatus").html("Error / No Connection &#8635;");$("#conStatus").off();$("#conStatus").on({click:restart});}
function handleVisibilityChange(){if(!websockConnected&&!document.hidden){restart();}}
function start(){document.addEventListener("visibilitychange",handleVisibilityChange,false);websock=new WebSocket("ws://"+window.location.hostname+"/ws");websock.onopen=function(evt){console.log("websock open");$("#conStatus").addClass("color-green");$("#conStatus").text("Connected");websockConnected=true;};websock.onclose=function(evt){console.log("websock close");conStatusError();};websock.onerror=function(evt){console.log(evt);conStatusError();};var handleEvent=function(evt){var data=JSON.parse(evt.data);var e=document.body;var center="";switch(data.type){case UI_INITIAL_GUI:data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element)};handleEvent(fauxEvent);});break;case UI_BATCH_UPDATE:data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element)};handleEvent(fauxEvent);});break;case UI_TITEL:document.title=data.label;$("#mainHeader").html(data.label);break;case UI_LABEL:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<span id='l"+data.id+"' class='label label-wrap'>"+data.value+"</span>"+
"</div>");break;case UI_BUTTON:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='one columns card tcenter "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<button id='btn"+data.id+"' "+
"onmousedown='buttonclick("+data.id+", true)' "+
"onmouseup='buttonclick("+data.id+", false)'>"+
data.value+
"</button></div>");$("#btn"+data.id).on({touchstart:function(e){e.preventDefault();buttonclick(data.id,true);},touchend:function(e){e.preventDefault();buttonclick(data.id,false);}});break;case UI_SWITCHER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='one columns card tcenter "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<label id='sl"+data.id+"' class='switch "+((data.value=="1")?"checked":"")+"'>"+
"<div class='in'><input type='checkbox' id='s"+data.id+"' onClick='switcher("+data.id+",null)' "+((data.value=="1")?"checked":"")+"/></div>"+
"</label>"+
"</div>");switcher(data.id,data.value);break;case UI_CPAD:case UI_PAD:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<nav class='control'>"+
"<ul>"+
"<li><a onmousedown='padclick(UP, "+data.id+", true)' onmouseup='padclick(UP, "+data.id+", false)' id='pf"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(RIGHT, "+data.id+", true)' onmouseup='padclick(RIGHT, "+data.id+", false)' id='pr"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(LEFT, "+data.id+", true)' onmouseup='padclick(LEFT, "+data.id+", false)' id='pl"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(DOWN, "+data.id+", true)' onmouseup='padclick(DOWN, "+data.id+", false)' id='pb"+data.id+"'>▲</a></li>"+
"</ul>"+
((data.type==UI_CPAD)?"<a class='confirm' onmousedown='padclick(CENTER,"+data.id+", true)' onmouseup='padclick(CENTER, "+data.id+", false)' id='pc"+data.id+"'>OK</a>":"")+
"</nav>"+
"</div>");$("#pf"+data.id).on({touchstart:function(e){e.preventDefault();padclick(UP,data.id,true);},touchend:function(e){e.preventDefault();padclick(UP,data.id,false);}});$("#pl"+data.id).on({touchstart:function(e){e.preventDefault();padclick(LEFT,data.id,true);},touchend:function(e){e.preventDefault();padclick(LEFT,data.id,false);}});$("#pr"+data.id).on({touchstart:function(e){e.preventDefault();padclick(RIGHT,data.id,true);},touchend:function(e){e.preventDefault();padclick(RIGHT,data.id,false);}});$("#pb"+data.id).on({touchstart:function(e){e.preventDefault();padclick(DOWN,data.id,true);},touchend:function(e){e.preventDefault();padclick(DOWN,data.id,false);}});$("#pc"+data.id).on({touchstart:function(e){e.preventDefault();padclick(CENTER,data.id,true);},touchend:function(e){e.preventDefault();padclick(CENTER,data.id,false);}});break;case UI_SLIDER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter card-slider "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<div class='range-slider'>"+
"<input id='sl"+data.id+"' type='range' min='0' max='100' value='"+data.value+"' class='range-slider__range'>"+
"<span class='range-slider__value'>"+data.value+"</span>"+
"</div>"+
"</div>");rangeSlider();break;case UI_NUMBER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<input style='color:black;' id='num"+data.id+"' type='number' value='"+data.value+"' onchange='numberchange("+data.id+")' />"+
"</div>");break;case UI_TEXT_INPUT:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<input style='color:black;' id='text"+data.id+"' value='"+data.value+"' onchange='textchange("+data.id+")' />"+
"</div>");break;case UI_TAB:$("#tabsnav").append("<li><a href='#tab"+data.id+"'>"+data.value+"</a></li>");$("#tabscontent").append("<div id='tab"+data.id+"'></div>");tabs=$('.tabscontent').tabbedContent({loop:true}).data('api');$('a').filter(function(){return $(this).attr('href')==='#click-to-switch';}).on('click',function(e){var tab=prompt('Tab to switch to (number or id)?');if(!tabs.switchTab(tab)){alert('That tab does not exist :\\');}
e.preventDefault();});break;case UI_SELECT:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.color)+"'>"+
"<h5>"+data.label+"</h5><hr/>"+
"<select style='color:black;' id='select"+data.id+"' onchange='selectchange("+data.id+")' />"+
"</div>");break;case UI_OPTION:if(data.parentControl){var parent=$("#select"+data.parentControl);parent.append("<option id='option"+data.id+"' value='"+data.value+"' "+data.selected+">"+data.label+"</option>");}
break;case UI_MIN:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){console.log("MIN"+data.value);parent.attr("min",data.value);}}
break;case UI_MAX:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){console.log("MAX"+data.value);parent.attr("max",data.value);}}
break;case UI_STEP:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){console.log("STEP"+data.value);parent.attr("step",data.value);}}
break;case UPDATE_LABEL:$("#l"+data.id).html(data.value);break;case UPDATE_SWITCHER:switcher(data.id,(data.value=="0")?0:1);break;case UPDATE_SLIDER:slider_move($("#sl"+data.id),data.value,"100",false);break;case UPDATE_NUMBER:$("#num"+data.id).val(data.value);break;case UPDATE_TEXT_INPUT:$("#text"+data.id).val(data.value);break;case UPDATE_SELECT:$("#select"+data.id).val(data.value);break;case UPDATE_BUTTON:case UPDATE_PAD:case UPDATE_CPAD:break;default:console.error("Unknown type or event");break;}
if(data.type>=UPDATE_OFFSET&&data.type<UI_INITIAL_GUI){var element=$('#id'+data.id);element.removeClass("turquoise emerald peterriver wetasphalt sunflower carrot alizarin");element.addClass(colorClass(data.color));}};websock.onmessage=handleEvent;}
function sliderchange(number){var val=$("#sl"+number).val();console.log("slvalue:"+val+":"+number);websock.send("slvalue:"+val+":"+number);}
function numberchange(number){var val=$("#num"+number).val();websock.send("nvalue:"+val+":"+number);}
function textchange(number){var val=$("#text"+number).val();websock.send("tvalue:"+val+":"+number);}
function selectchange(number){var val=$("#select"+number).val();websock.send("svalue:"+val+":"+number);}
function buttonclick(number,isdown){if(isdown)websock.send("bdown:"+number);else websock.send("bup:"+number);}
function padclick(type,number,isdown){switch(type){case CENTER:if(isdown)websock.send("pcdown:"+number);else websock.send("pcup:"+number);break;case UP:if(isdown)websock.send("pfdown:"+number);else websock.send("pfup:"+number);break;case DOWN:if(isdown)websock.send("pbdown:"+number);else websock.send("pbup:"+number);break;case LEFT:if(isdown)websock.send("pldown:"+number);else websock.send("plup:"+number);break;case RIGHT:if(isdown)websock.send("prdown:"+number);else websock.send("prup:"+number);break;}}
function switcher(number,state){if(state==null){if($("#s"+number).is(":checked")){websock.send("sactive:"+number);$("#sl"+number).addClass("checked");}else{websock.send("sinactive:"+number);$("#sl"+number).removeClass("checked");}}else if(state==1){$("#sl"+number).addClass("checked");$("#sl"+number).prop("checked",true);}else if(state==0){$("#sl"+number).removeClass("checked");$("#sl"+number).prop("checked",false);}}
var rangeSlider=function(){var slider=$('.range-slider'),range=$('.range-slider__range'),value=$('.range-slider__value');slider.each(function(){value.each(function(){var value=$(this).prev().attr('value');$(this).html(value);});range.on({'input':function(){$(this).next().html(this.value);},'change':function(){sliderchange($(this).attr('id').replace(/^\D+/g,''));}});});};
)=====";

const uint8_t JS_CONTROLS_GZIP[2801] PROGMEM = { 31,139,8,0,125,71,101,94,2,255,237,90,253,114,219,184,17,255,63,79,193,227,101,66,178,86,244,145,156,115,57,210,116,70,145,149,68,61,69,118,109,249,146,233,100,170,129,68,40,226,152,34,89,18,178,156,243,232,53,250,32,125,164,62,73,23,95,36,64,81,182,46,110,175,237,164,51,25,71,92,44,126,248,97,119,1,44,62,102,73,156,19,227,114,48,25,140,6,227,65,119,56,121,123,57,240,159,181,219,222,76,22,188,238,142,123,239,38,151,103,39,221,113,31,74,58,178,132,9,38,167,111,222,92,244,199,126,71,173,49,30,140,251,67,95,17,156,117,79,252,74,61,38,42,193,6,147,30,149,60,211,149,122,92,235,153,66,230,114,60,62,29,249,207,117,61,33,237,180,159,151,154,195,238,107,32,241,131,174,200,133,157,246,15,165,222,197,135,1,244,175,127,238,31,234,170,133,188,211,62,84,180,135,131,19,144,189,168,232,114,105,167,253,162,212,28,93,190,127,13,178,31,117,77,33,237,180,127,84,204,213,255,56,6,243,159,93,142,253,151,186,182,82,210,105,191,44,107,188,61,239,158,189,243,127,18,130,238,201,9,151,76,206,78,7,35,170,42,10,122,195,126,247,92,40,119,218,63,41,45,118,95,251,157,138,67,184,76,113,200,69,127,216,239,1,90,197,39,82,220,81,188,114,122,54,30,80,251,87,220,34,197,29,197,45,239,7,32,168,120,133,201,58,138,79,222,119,63,250,157,138,63,152,172,163,186,98,220,63,243,59,85,79,48,161,34,45,194,240,228,244,195,168,8,194,97,255,205,184,8,182,243,193,219,119,227,34,164,122,253,209,24,60,36,217,244,38,227,203,243,63,93,158,14,46,250,5,84,111,210,127,223,63,239,14,203,160,238,77,206,250,80,235,124,240,11,84,125,86,8,63,244,199,221,139,179,119,221,161,2,63,185,184,28,189,25,158,126,208,218,232,117,207,207,79,199,69,8,246,38,221,225,224,207,221,115,176,203,139,66,116,210,61,255,185,8,167,222,100,116,58,130,225,120,120,232,205,87,241,140,132,73,108,204,146,40,201,122,17,202,115,155,253,28,4,206,173,248,225,143,86,203,41,206,10,185,151,175,67,50,91,40,122,40,199,106,95,221,12,147,85,22,155,240,231,175,171,36,204,177,233,9,21,209,117,169,128,151,56,67,81,80,20,151,118,144,26,41,38,56,203,194,107,156,21,74,165,93,164,210,26,19,148,167,11,20,145,66,169,176,147,212,201,87,241,60,74,214,10,14,55,155,44,159,161,44,75,202,250,210,132,178,24,69,225,175,40,11,227,66,129,90,80,22,6,40,187,50,189,0,207,209,42,34,82,104,122,155,205,163,107,148,25,107,60,205,147,217,149,167,252,238,37,113,140,103,4,7,254,28,69,57,46,189,144,225,156,160,140,216,206,237,99,59,72,102,171,37,142,137,211,68,65,96,155,127,48,157,102,50,159,219,142,247,216,54,191,207,146,53,124,47,200,50,178,77,211,241,4,110,115,22,37,57,6,21,129,226,109,30,41,14,142,47,8,34,171,188,15,29,205,160,133,29,92,40,122,161,11,109,100,120,153,92,99,30,25,38,115,249,211,207,25,198,177,233,108,169,2,79,77,47,195,65,141,22,39,205,88,24,45,99,148,24,130,1,37,249,228,251,151,47,158,31,122,53,181,202,174,107,210,216,190,157,69,225,236,202,21,150,219,104,125,94,160,56,136,240,47,97,30,78,195,40,36,95,122,32,248,12,246,185,13,231,246,119,213,254,63,121,242,157,52,121,115,17,6,1,142,157,219,194,31,212,153,5,172,244,81,161,14,29,239,95,195,143,97,152,19,28,195,80,49,175,139,54,103,172,77,179,81,207,165,193,140,94,56,208,143,241,218,248,128,167,23,240,27,19,219,92,231,110,171,101,30,172,195,56,72,214,205,40,153,33,74,160,185,72,114,18,163,37,62,48,91,235,92,113,127,18,39,41,142,125,73,212,198,215,132,142,226,56,79,34,12,181,63,3,32,215,52,168,222,30,30,220,229,105,130,111,128,93,97,186,146,66,25,77,36,91,97,111,163,80,99,177,185,15,55,166,8,144,213,136,213,208,48,149,221,129,70,5,117,8,116,20,114,87,48,143,85,16,104,105,128,8,242,255,120,113,58,106,166,40,131,209,4,5,77,42,115,88,93,236,23,94,159,38,193,23,38,155,193,23,206,124,24,242,98,102,164,234,77,242,37,197,98,110,212,51,36,151,21,3,55,146,37,81,222,156,39,89,31,65,37,28,97,10,235,31,51,22,48,151,220,112,134,183,84,221,101,132,114,2,83,208,231,112,254,69,42,59,27,79,233,140,93,84,130,158,58,222,52,195,232,202,147,4,212,76,236,63,195,128,101,118,110,97,62,18,146,8,172,73,153,68,104,138,35,22,100,75,20,198,239,48,10,96,158,22,51,69,169,80,197,99,249,152,75,169,130,163,0,209,131,81,205,180,249,103,143,119,207,185,229,159,62,133,39,104,106,30,212,232,120,27,12,195,80,213,100,19,236,230,17,151,52,81,10,227,5,38,225,163,32,188,54,194,192,183,194,64,224,132,193,129,105,65,200,194,160,241,45,178,78,232,66,186,90,198,185,1,11,74,96,16,30,26,134,121,160,172,175,194,248,240,237,64,221,99,243,224,145,121,180,56,60,22,128,172,171,7,230,81,11,68,71,139,172,197,203,243,20,197,172,225,168,174,93,86,199,96,127,159,174,51,148,90,18,236,26,69,43,76,193,104,125,142,212,130,46,28,155,91,209,193,146,224,255,42,99,194,24,255,55,25,115,186,34,36,225,230,156,146,88,107,155,150,39,241,50,89,229,24,102,220,24,20,152,46,91,99,108,69,179,97,208,249,205,209,42,172,210,59,212,249,60,207,8,42,158,161,254,224,85,142,11,199,80,131,169,180,248,42,71,146,213,108,193,22,30,183,156,178,156,91,220,76,51,76,199,219,9,207,62,96,142,83,41,8,136,6,35,235,109,26,12,5,140,255,53,24,98,165,218,108,141,107,185,217,249,70,162,135,15,54,218,114,94,59,24,249,26,0,237,216,118,233,105,223,55,59,166,243,202,4,235,195,202,30,152,46,100,109,69,139,180,39,162,114,24,91,199,71,97,156,174,136,65,215,15,223,98,21,166,201,141,197,91,212,26,76,226,30,245,144,108,146,230,29,74,200,197,171,40,98,1,122,63,143,150,140,62,22,144,172,131,250,100,81,52,32,131,161,68,172,70,3,221,118,187,242,131,254,254,54,38,232,24,21,62,20,235,170,168,184,18,166,140,194,227,35,100,104,115,75,138,2,62,196,46,207,26,70,221,228,162,76,44,187,117,197,204,194,122,157,206,213,94,31,255,227,111,127,63,106,33,112,46,52,126,47,9,182,147,221,159,71,157,186,70,37,251,122,42,116,135,189,63,147,26,109,141,72,244,245,68,232,190,127,127,34,53,218,26,145,233,221,68,90,60,84,236,50,125,244,125,49,160,96,196,2,199,50,190,230,97,182,180,118,112,230,103,16,141,125,73,11,245,59,104,207,52,218,167,63,83,214,124,226,160,164,33,240,245,185,130,14,78,37,14,127,235,242,165,6,250,215,46,95,117,24,202,242,197,24,70,15,103,200,2,239,193,28,53,148,42,203,236,225,44,249,64,125,48,77,29,166,202,115,250,112,158,108,244,60,152,166,134,82,101,57,123,56,75,49,92,30,204,179,130,179,59,185,98,167,195,255,27,139,40,253,120,154,71,97,240,175,88,80,149,164,40,163,39,37,2,88,212,230,41,82,77,18,198,179,38,86,195,50,150,33,76,140,109,248,31,221,248,86,167,13,191,120,18,100,233,219,35,171,174,161,201,132,131,40,251,175,90,45,134,113,255,134,75,157,33,25,192,5,171,111,87,253,205,207,248,191,145,164,137,123,49,39,95,34,154,233,210,186,238,52,66,179,43,143,175,60,241,106,89,227,219,152,157,70,239,116,37,108,91,216,201,154,84,228,95,106,102,12,235,90,235,174,189,112,121,113,242,127,55,80,58,244,176,79,35,116,175,229,105,141,175,176,123,247,181,43,236,152,67,86,65,143,35,165,101,120,142,182,200,240,220,183,20,59,243,140,164,58,244,100,78,197,39,125,138,70,51,114,176,149,138,40,109,93,5,43,184,209,122,224,44,171,169,0,88,14,253,154,226,160,199,191,237,219,40,73,82,151,46,2,27,135,29,18,218,22,74,67,139,182,108,33,208,158,135,17,120,200,46,22,5,122,162,76,111,7,140,199,54,89,132,57,240,33,36,179,45,218,49,203,241,125,232,28,91,29,158,146,228,41,223,114,89,222,134,45,85,22,147,91,13,117,121,161,193,9,116,252,52,75,150,41,177,173,49,154,26,36,49,196,254,19,126,217,124,4,24,73,6,93,117,94,1,45,122,238,77,251,211,228,74,80,195,134,79,199,185,69,17,206,40,196,2,17,138,105,4,9,206,141,56,33,6,190,9,115,98,184,159,62,89,244,100,189,102,69,219,94,177,216,29,223,183,114,46,135,35,60,187,99,236,240,242,202,174,93,14,19,94,248,219,7,10,191,26,117,119,152,181,52,60,51,152,198,160,98,221,170,21,147,148,221,111,80,226,252,231,62,195,94,124,243,118,48,104,110,89,140,99,209,126,108,30,233,61,121,63,216,183,27,133,99,53,181,3,211,96,147,151,201,66,91,116,39,15,127,197,182,83,185,92,128,150,84,226,101,223,233,0,52,33,81,48,181,51,141,205,22,211,238,199,223,139,105,247,227,93,76,209,205,61,76,233,45,246,239,68,149,54,117,7,215,156,224,244,78,178,202,187,10,54,243,171,123,178,242,240,191,230,152,73,127,101,225,110,29,79,233,39,94,109,211,121,213,118,59,181,16,60,189,22,201,28,189,233,180,217,160,81,152,40,29,104,152,144,68,154,50,89,223,70,19,201,27,69,80,115,23,135,214,190,167,47,74,210,193,38,68,117,205,221,167,190,152,117,183,70,252,126,181,197,241,191,42,42,143,241,202,231,52,46,175,41,111,186,101,44,176,187,56,219,188,140,175,226,100,29,179,52,141,174,57,108,161,40,38,175,205,35,25,147,180,252,216,215,158,0,61,121,82,148,28,233,151,101,60,102,229,205,20,44,171,16,180,86,209,53,79,20,232,183,212,197,187,3,67,60,48,48,202,103,4,70,249,88,192,40,222,4,24,252,246,223,40,110,249,75,224,226,70,180,126,161,160,33,173,220,74,46,113,158,35,152,218,149,43,49,245,62,154,135,153,152,240,249,226,204,251,7,142,241,101,220,9,57,243,26,187,194,44,199,91,30,49,15,186,230,1,252,127,96,186,133,114,65,33,103,19,249,110,61,133,140,150,30,215,145,97,33,172,179,209,155,137,247,104,69,73,5,235,218,224,113,126,87,35,100,143,70,180,133,180,214,174,98,72,220,213,80,190,71,67,234,189,8,47,110,132,57,61,127,99,79,10,196,79,29,118,74,101,10,26,77,104,140,138,202,42,173,111,174,56,45,160,3,163,81,105,80,220,53,43,215,204,252,76,193,221,197,36,157,221,79,37,157,105,92,180,153,98,55,240,124,15,224,249,46,96,122,98,179,27,122,15,243,165,211,93,208,244,104,109,55,116,180,7,116,180,11,154,29,135,237,198,206,246,192,206,106,176,181,103,38,114,85,19,142,207,9,34,152,5,26,251,229,251,236,134,135,126,179,16,47,163,59,132,57,208,149,55,60,78,241,210,71,198,57,2,248,107,172,52,93,157,121,148,87,32,18,68,36,226,21,164,48,190,23,75,127,62,84,194,49,60,163,236,75,135,62,121,186,159,70,85,7,246,62,105,89,46,143,227,42,216,237,109,236,29,180,238,129,47,78,233,216,195,46,229,24,199,87,118,120,180,136,79,244,108,251,168,29,94,57,13,246,185,85,32,15,155,156,6,207,89,182,203,249,49,147,227,241,239,38,166,239,53,180,70,161,184,70,154,25,18,144,239,55,233,246,205,150,219,78,137,41,11,89,202,37,51,53,113,76,197,206,73,45,150,15,90,174,2,45,235,196,244,37,144,168,74,37,69,166,215,176,248,124,172,213,210,22,64,125,15,12,203,58,117,75,10,155,39,108,183,254,242,233,228,160,245,185,97,89,14,63,20,165,255,188,127,2,84,109,12,158,111,44,0,0 };
