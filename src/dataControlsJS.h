const char JS_CONTROLS[] PROGMEM = R"=====(
const UI_INITIAL_GUI=200;const UI_BATCH_UPDATE=201;const UPDATE_OFFSET=100;const UI_TITEL=0;const UI_PAD=1;const UPDATE_PAD=101;const UI_CPAD=2;const UPDATE_CPAD=102;const UI_BUTTON=3;const UPDATE_BUTTON=103;const UI_LABEL=4;const UPDATE_LABEL=104;const UI_SWITCHER=5;const UPDATE_SWITCHER=105;const UI_SLIDER=6;const UPDATE_SLIDER=106;const UI_NUMBER=7;const UPDATE_NUMBER=107;const UI_TEXT_INPUT=8;const UPDATE_TEXT_INPUT=108;const UI_GRAPH=9;const ADD_GRAPH_POINT=10;const CLEAR_GRAPH=109;const UI_TAB=11;const UPDATE_TAB=111;const UI_SELECT=12;const UPDATE_SELECT=112;const UI_OPTION=13;const UPDATE_OPTION=113;const UI_MIN=14;const UPDATE_MIN=114;const UI_MAX=15;const UPDATE_MAX=115;const UI_STEP=16;const UPDATE_STEP=116;const UP=0;const DOWN=1;const LEFT=2;const RIGHT=3;const CENTER=4;const C_TURQUOISE=0;const C_EMERALD=1;const C_PETERRIVER=2;const C_WETASPHALT=3;const C_SUNFLOWER=4;const C_CARROT=5;const C_ALIZARIN=6;const C_DARK=7;const C_NONE=255;function colorClass(colorId){colorId=Number(colorId);switch(colorId){case C_TURQUOISE:return"turquoise";case C_EMERALD:return"emerald";case C_PETERRIVER:return"peterriver";case C_WETASPHALT:return"wetasphalt";case C_SUNFLOWER:return"sunflower";case C_CARROT:return"carrot";case C_ALIZARIN:return"alizarin";case C_NONE:return"dark";default:return"";}}
var websock;var websockConnected=false;function restart(){$(document).add("*").off();$("#row").html("");websock.close();start();}
function conStatusError(){websockConnected=false;$("#conStatus").removeClass("color-green");$("#conStatus").addClass("color-red");$("#conStatus").html("Error / No Connection &#8635;");$("#conStatus").off();$("#conStatus").on({click:restart});}
function handleVisibilityChange(){if(!websockConnected&&!document.hidden){restart();}}
function start(){document.addEventListener("visibilitychange",handleVisibilityChange,false);websock=new WebSocket("ws://"+window.location.hostname+"/ws");websock.onopen=function(evt){console.log("websock open");$("#conStatus").addClass("color-green");$("#conStatus").text("Connected");websockConnected=true;};websock.onclose=function(evt){console.log("websock close");conStatusError();};websock.onerror=function(evt){console.log(evt);conStatusError();};var handleEvent=function(evt){var data=JSON.parse(evt.data);var e=document.body;var center="";switch(data.t){case UI_INITIAL_GUI:data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element)};handleEvent(fauxEvent);});break;case UI_BATCH_UPDATE:data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element)};handleEvent(fauxEvent);});break;case UI_TITEL:document.title=data.l;$("#mainHeader").html(data.l);break;case UI_LABEL:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<span id='l"+data.id+"' class='label label-wrap'>"+data.v+"</span>"+
"</div>");break;case UI_BUTTON:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='one columns card tcenter "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<button id='btn"+data.id+"' "+
"onmousedown='buttonclick("+data.id+", true)' "+
"onmouseup='buttonclick("+data.id+", false)'>"+
data.v+
"</button></div>");$("#btn"+data.id).on({touchstart:function(e){e.preventDefault();buttonclick(data.id,true);},touchend:function(e){e.preventDefault();buttonclick(data.id,false);}});break;case UI_SWITCHER:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='one columns card tcenter "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<label id='sl"+data.id+"' class='switch "+((data.v=="1")?"checked":"")+"'>"+
"<div class='in'><input type='checkbox' id='s"+data.id+"' onClick='switcher("+data.id+",null)' "+((data.v=="1")?"checked":"")+"/></div>"+
"</label>"+
"</div>");switcher(data.id,data.v);break;case UI_CPAD:case UI_PAD:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<nav class='control'>"+
"<ul>"+
"<li><a onmousedown='padclick(UP, "+data.id+", true)' onmouseup='padclick(UP, "+data.id+", false)' id='pf"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(RIGHT, "+data.id+", true)' onmouseup='padclick(RIGHT, "+data.id+", false)' id='pr"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(LEFT, "+data.id+", true)' onmouseup='padclick(LEFT, "+data.id+", false)' id='pl"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(DOWN, "+data.id+", true)' onmouseup='padclick(DOWN, "+data.id+", false)' id='pb"+data.id+"'>▲</a></li>"+
"</ul>"+
((data.t==UI_CPAD)?"<a class='confirm' onmousedown='padclick(CENTER,"+data.id+", true)' onmouseup='padclick(CENTER, "+data.id+", false)' id='pc"+data.id+"'>OK</a>":"")+
"</nav>"+
"</div>");$("#pf"+data.id).on({touchstart:function(e){e.preventDefault();padclick(UP,data.id,true);},touchend:function(e){e.preventDefault();padclick(UP,data.id,false);}});$("#pl"+data.id).on({touchstart:function(e){e.preventDefault();padclick(LEFT,data.id,true);},touchend:function(e){e.preventDefault();padclick(LEFT,data.id,false);}});$("#pr"+data.id).on({touchstart:function(e){e.preventDefault();padclick(RIGHT,data.id,true);},touchend:function(e){e.preventDefault();padclick(RIGHT,data.id,false);}});$("#pb"+data.id).on({touchstart:function(e){e.preventDefault();padclick(DOWN,data.id,true);},touchend:function(e){e.preventDefault();padclick(DOWN,data.id,false);}});$("#pc"+data.id).on({touchstart:function(e){e.preventDefault();padclick(CENTER,data.id,true);},touchend:function(e){e.preventDefault();padclick(CENTER,data.id,false);}});break;case UI_SLIDER:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter card-slider "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<div class='range-slider'>"+
"<input id='sl"+data.id+"' type='range' min='0' max='100' value='"+data.v+"' class='range-slider__range'>"+
"<span class='range-slider__value'>"+data.v+"</span>"+
"</div>"+
"</div>");rangeSlider();break;case UI_NUMBER:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<input style='color:black;' id='num"+data.id+"' type='number' value='"+data.v+"' onchange='numberchange("+data.id+")' />"+
"</div>");break;case UI_TEXT_INPUT:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<input style='color:black;' id='text"+data.id+"' value='"+data.v+"' onchange='textchange("+data.id+")' />"+
"</div>");break;case UI_TAB:$("#tabsnav").append("<li><a href='#tab"+data.id+"'>"+data.v+"</a></li>");$("#tabscontent").append("<div id='tab"+data.id+"'></div>");tabs=$('.tabscontent').tabbedContent({loop:true}).data('api');$('a').filter(function(){return $(this).attr('href')==='#click-to-switch';}).on('click',function(e){var tab=prompt('Tab to switch to (number or id)?');if(!tabs.switchTab(tab)){alert('That tab does not exist :\\');}
e.preventDefault();});break;case UI_SELECT:var parent;if(data.pc){parent=$("#tab"+data.pc);}else{parent=$("#row")}
parent.append("<div id='id"+data.id+"' class='two columns card tcenter "+colorClass(data.c)+"'>"+
"<h5>"+data.l+"</h5><hr/>"+
"<select style='color:black;' id='select"+data.id+"' onchange='selectchange("+data.id+")' />"+
"</div>");break;case UI_OPTION:if(data.pc){var parent=$("#select"+data.pc);parent.append("<option id='option"+data.id+"' value='"+data.v+"' "+data.s+">"+data.l+"</option>");}
break;case UI_MIN:if(data.pc){var parent=$("#id"+data.pc+" input");if(parent.size()){parent.attr("min",data.v);}}
break;case UI_MAX:if(data.pc){var parent=$("#id"+data.pc+" input");if(parent.size()){parent.attr("max",data.v);}}
break;case UI_STEP:if(data.pc){var parent=$("#id"+data.pc+" input");if(parent.size()){parent.attr("step",data.v);}}
break;case UPDATE_LABEL:$("#l"+data.id).html(data.v);break;case UPDATE_SWITCHER:switcher(data.id,(data.v=="0")?0:1);break;case UPDATE_SLIDER:slider_move($("#sl"+data.id),data.v,"100",false);break;case UPDATE_NUMBER:$("#num"+data.id).val(data.v);break;case UPDATE_TEXT_INPUT:$("#text"+data.id).val(data.v);break;case UPDATE_SELECT:$("#select"+data.id).val(data.v);break;case UPDATE_BUTTON:case UPDATE_PAD:case UPDATE_CPAD:break;default:console.error("Unknown type or event");break;}
if(data.t>=UPDATE_OFFSET&&data.t<UI_INITIAL_GUI){var element=$('#id'+data.id);element.removeClass("turquoise emerald peterriver wetasphalt sunflower carrot alizarin");element.addClass(colorClass(data.c));}};websock.onmessage=handleEvent;}
function sliderchange(number){var val=$("#sl"+number).val();console.log("slvalue:"+val+":"+number);websock.send("slvalue:"+val+":"+number);}
function numberchange(number){var val=$("#num"+number).val();websock.send("nvalue:"+val+":"+number);}
function textchange(number){var val=$("#text"+number).val();websock.send("tvalue:"+val+":"+number);}
function selectchange(number){var val=$("#select"+number).val();websock.send("svalue:"+val+":"+number);}
function buttonclick(number,isdown){if(isdown)websock.send("bdown:"+number);else websock.send("bup:"+number);}
function padclick(type,number,isdown){switch(type){case CENTER:if(isdown)websock.send("pcdown:"+number);else websock.send("pcup:"+number);break;case UP:if(isdown)websock.send("pfdown:"+number);else websock.send("pfup:"+number);break;case DOWN:if(isdown)websock.send("pbdown:"+number);else websock.send("pbup:"+number);break;case LEFT:if(isdown)websock.send("pldown:"+number);else websock.send("plup:"+number);break;case RIGHT:if(isdown)websock.send("prdown:"+number);else websock.send("prup:"+number);break;}}
function switcher(number,state){if(state==null){if($("#s"+number).is(":checked")){websock.send("sactive:"+number);$("#sl"+number).addClass("checked");}else{websock.send("sinactive:"+number);$("#sl"+number).removeClass("checked");}}else if(state==1){$("#sl"+number).addClass("checked");$("#sl"+number).prop("checked",true);}else if(state==0){$("#sl"+number).removeClass("checked");$("#sl"+number).prop("checked",false);}}
var rangeSlider=function(){var slider=$('.range-slider'),range=$('.range-slider__range'),value=$('.range-slider__value');slider.each(function(){value.each(function(){var value=$(this).prev().attr('value');$(this).html(value);});range.on({'input':function(){$(this).next().html(this.value);},'change':function(){sliderchange($(this).attr('id').replace(/^\D+/g,''));}});});};
)=====";

const uint8_t JS_CONTROLS_GZIP[2764] PROGMEM = { 31,139,8,0,62,106,105,94,2,255,229,90,253,110,219,200,17,255,63,79,193,227,5,33,89,41,250,72,206,185,28,105,58,80,100,37,81,79,145,93,91,190,4,69,80,129,34,87,17,97,138,100,201,149,229,156,161,215,232,131,244,145,250,36,157,253,34,119,41,74,214,197,1,174,72,129,192,33,103,103,127,243,227,204,236,236,151,252,36,206,177,118,53,156,14,199,195,201,176,55,154,190,189,26,186,207,58,29,199,23,13,175,123,147,254,187,233,213,249,105,111,50,128,150,174,104,161,130,233,217,155,55,151,131,137,219,149,123,76,134,147,193,200,149,4,231,189,83,183,210,143,138,74,176,225,180,79,36,207,84,165,62,211,122,38,145,185,154,76,206,198,238,115,85,143,75,187,157,231,165,230,168,247,26,72,252,164,42,50,97,183,243,83,169,119,249,97,8,223,55,184,112,143,84,213,66,222,237,28,73,218,163,225,41,200,94,84,116,153,180,219,121,81,106,142,175,222,191,6,217,207,170,38,151,118,59,63,75,238,26,124,156,128,251,207,175,38,238,75,85,91,106,233,118,94,150,61,222,94,244,206,223,185,191,112,65,239,244,148,73,166,231,103,195,49,81,229,13,253,209,160,119,193,149,187,157,95,36,139,189,215,110,183,18,16,38,147,2,114,57,24,13,250,128,86,137,137,16,119,165,168,156,157,79,134,196,255,149,176,8,113,87,10,203,251,33,8,42,81,161,178,174,20,147,247,189,143,110,183,18,15,42,235,202,161,152,12,206,221,110,53,18,84,40,73,139,52,60,61,251,48,46,146,112,52,120,51,41,146,237,98,248,246,221,164,72,169,254,96,60,129,8,9,54,253,233,228,234,226,111,87,103,195,203,65,1,213,159,14,222,15,46,122,163,50,169,251,211,243,1,244,186,24,254,6,93,159,21,194,15,131,73,239,242,252,93,111,36,193,79,47,175,198,111,70,103,31,20,27,253,222,197,197,217,164,72,193,254,180,55,26,254,189,119,1,126,121,81,136,78,123,23,191,22,233,212,159,142,207,198,48,28,143,142,156,249,42,246,113,152,196,154,159,68,73,214,143,188,60,55,233,227,48,176,238,248,131,59,94,45,103,40,43,228,78,190,14,177,191,144,244,188,28,201,223,106,103,8,175,178,88,135,63,255,92,37,97,142,116,135,171,240,79,23,10,104,137,50,47,10,138,230,210,15,66,35,69,24,101,89,120,131,178,66,169,244,139,80,90,35,236,229,233,194,139,112,161,84,248,73,232,228,171,120,30,37,107,9,135,185,77,180,251,94,150,37,101,127,225,66,209,236,69,225,239,94,22,198,133,2,241,160,104,12,188,236,90,119,2,52,247,86,17,22,66,221,217,108,30,221,120,153,182,70,179,60,241,175,29,233,185,159,196,49,242,49,10,220,185,23,229,168,140,66,134,114,236,101,216,180,238,30,155,65,226,175,150,40,198,86,203,11,2,83,255,139,110,181,146,249,220,180,156,199,166,254,99,150,172,225,125,129,151,145,169,235,150,195,113,91,126,148,228,8,84,56,138,179,121,36,5,56,190,196,30,94,229,3,248,208,12,44,236,224,66,208,11,93,176,145,161,101,114,131,88,102,232,52,228,79,63,103,8,197,186,181,165,10,60,21,189,12,5,53,90,140,52,101,161,181,181,113,162,113,6,132,228,147,31,95,190,120,126,228,212,244,42,63,93,145,198,230,157,31,133,254,181,205,61,183,81,190,121,225,197,65,132,126,11,243,112,22,70,33,254,210,7,193,103,240,207,93,56,55,127,168,126,255,147,39,63,8,151,183,22,97,16,160,216,186,43,226,65,130,89,192,138,24,21,234,240,225,131,27,120,24,133,57,70,49,12,21,253,166,176,233,83,155,122,179,158,75,147,58,189,8,160,27,163,181,246,1,205,46,225,25,97,83,95,231,118,187,173,55,214,97,28,36,235,86,148,248,30,33,208,90,36,57,142,189,37,106,232,237,117,46,133,63,137,147,20,197,174,32,106,162,27,76,70,113,156,39,17,130,222,159,1,144,105,106,68,239,128,8,238,138,52,70,183,192,174,112,93,73,161,204,38,156,173,144,179,145,168,209,220,60,132,27,85,4,200,106,198,42,104,136,200,246,160,17,65,29,2,25,133,44,20,52,98,21,4,210,26,120,216,115,255,122,121,54,110,165,94,6,163,9,26,90,68,102,209,190,200,45,162,62,75,130,47,84,230,195,27,202,92,24,242,188,50,18,245,22,230,133,81,93,30,217,180,13,136,225,44,137,242,214,60,201,6,30,244,64,17,34,152,238,9,165,0,133,228,150,209,187,35,234,54,101,147,99,168,63,159,195,249,23,161,108,109,28,233,75,204,162,19,124,166,229,204,50,228,93,59,130,128,188,12,251,115,24,208,101,157,93,248,14,135,56,2,87,18,38,17,205,174,165,23,198,239,144,23,64,129,230,37,130,53,86,113,232,34,204,38,20,33,58,128,228,192,80,166,154,169,111,221,49,145,75,240,176,55,211,27,162,193,217,32,24,101,114,51,173,159,155,71,76,210,242,82,24,14,80,99,143,131,240,70,11,3,215,8,3,222,57,12,26,186,1,25,9,99,194,53,240,58,33,243,228,106,25,231,26,204,23,129,134,89,228,53,189,33,77,159,204,189,22,244,59,209,27,143,244,227,197,209,9,7,139,26,250,113,27,94,143,23,89,155,181,229,169,23,83,131,81,157,189,200,155,161,72,163,127,159,174,51,47,53,4,208,13,1,34,125,25,74,27,104,159,232,91,49,167,235,218,63,201,85,48,64,191,177,171,102,43,140,19,230,172,25,142,21,155,164,61,137,151,201,42,71,80,38,99,80,160,186,116,98,48,37,205,166,70,138,146,165,116,88,165,123,212,89,113,166,228,184,223,137,183,153,250,73,225,118,226,36,153,18,155,150,112,178,242,23,116,166,176,203,26,99,221,161,86,154,33,50,70,78,217,114,1,138,146,108,158,67,52,41,81,103,211,164,40,224,240,175,193,224,83,203,102,107,44,138,221,201,119,147,27,108,160,16,139,121,237,64,98,101,25,240,77,6,123,227,186,122,87,183,94,233,224,91,152,104,3,221,134,69,84,97,137,176,231,29,195,216,56,57,14,227,116,133,53,252,37,69,174,65,59,204,146,91,131,89,83,140,37,113,159,248,95,152,35,203,0,41,153,226,85,20,209,212,219,207,161,45,242,138,166,26,253,48,117,144,23,224,34,204,12,173,26,99,178,251,181,197,11,121,254,94,74,102,236,21,209,225,115,24,239,180,226,142,138,194,147,99,79,83,234,65,234,5,108,104,92,157,55,181,186,130,32,21,131,221,186,188,26,208,175,77,231,242,215,158,252,231,95,255,62,110,123,16,58,48,126,47,9,186,101,60,156,71,157,186,66,37,251,122,42,100,43,123,56,147,26,109,133,72,244,245,68,200,6,251,112,34,53,218,10,145,217,126,34,109,150,42,124,32,98,215,229,227,5,6,35,16,44,147,107,30,102,75,99,7,97,182,211,111,30,202,152,171,239,225,236,43,156,207,126,37,148,89,77,32,140,33,235,213,50,64,70,164,148,132,127,116,206,145,179,252,107,231,156,58,12,105,206,161,12,163,135,51,164,89,247,96,142,10,74,149,101,246,112,150,108,148,62,152,166,10,83,229,57,123,56,79,58,116,30,76,83,65,169,178,244,31,206,146,15,151,7,243,172,224,236,94,17,209,51,216,255,181,57,146,188,60,205,163,48,120,200,124,41,173,102,50,114,226,192,1,121,79,182,182,169,89,57,177,229,14,237,97,104,203,16,74,95,7,254,247,110,93,163,219,129,167,27,47,90,65,123,185,31,49,234,140,76,167,12,64,218,236,212,106,81,180,253,187,27,185,246,209,206,151,180,175,89,141,36,59,35,255,110,86,59,44,62,57,254,18,145,197,39,193,176,103,145,231,95,59,108,214,136,87,203,154,168,197,244,188,182,54,72,176,71,160,231,78,66,137,189,201,11,85,152,143,218,251,182,149,229,181,194,255,139,147,201,97,151,66,100,175,95,137,246,87,120,181,247,218,230,14,203,97,174,39,71,113,194,27,108,217,180,200,208,220,53,36,135,178,117,130,60,100,196,18,135,149,97,130,68,22,200,224,27,25,77,248,182,10,84,240,34,253,32,56,70,75,2,48,44,242,54,67,65,159,189,155,119,81,146,164,54,41,203,27,139,30,142,153,134,151,134,6,177,108,120,160,61,15,35,136,136,89,148,105,114,146,74,78,197,181,199,38,94,132,57,240,193,56,51,13,242,81,134,229,186,240,97,180,94,63,197,201,83,182,191,49,156,13,157,60,12,42,55,154,114,193,39,105,7,116,220,52,75,150,41,54,141,137,55,211,112,162,241,77,30,60,153,44,183,181,36,131,79,181,94,1,45,114,222,75,190,167,197,148,160,135,9,175,150,117,231,69,40,35,16,11,15,19,76,45,72,80,174,197,9,214,208,109,152,99,205,254,244,201,32,39,202,53,115,204,246,28,66,239,182,190,159,163,41,20,33,127,207,168,96,237,149,13,176,24,4,172,241,143,15,3,118,233,103,203,142,43,253,73,189,163,152,37,254,171,250,41,73,233,25,61,161,200,30,239,27,186,252,57,111,232,138,51,88,103,66,113,243,72,37,249,126,184,151,97,17,160,212,111,232,26,173,45,58,205,64,206,52,15,127,71,166,37,50,130,141,4,29,102,88,189,216,201,111,182,44,246,62,126,123,139,222,237,30,139,228,42,244,155,155,204,49,74,119,218,148,238,216,105,37,148,119,14,229,121,112,229,156,67,189,109,183,183,206,70,202,163,150,142,110,189,234,216,221,218,238,108,241,199,23,35,228,182,203,164,153,38,49,224,164,155,58,44,126,116,177,140,220,70,226,139,15,210,91,158,153,173,22,164,221,30,254,210,148,74,235,131,60,223,220,215,151,87,157,173,161,113,127,79,126,62,44,139,202,51,163,242,39,20,54,235,41,110,55,197,29,11,189,127,49,245,171,248,58,134,141,49,93,120,144,122,75,139,100,49,172,55,143,68,10,225,19,87,249,205,199,147,39,76,124,172,222,142,176,60,19,87,17,48,153,64,162,25,197,7,57,188,65,189,147,44,110,153,53,126,157,172,149,151,198,90,121,53,172,21,55,192,26,187,235,213,138,59,221,18,184,184,255,218,46,154,36,97,165,251,167,37,202,115,15,74,157,116,255,33,223,60,178,100,226,5,144,77,71,236,219,32,38,174,200,46,46,167,113,162,151,85,229,93,88,30,209,74,101,235,13,248,191,161,219,133,114,65,33,167,229,110,183,158,68,70,89,234,213,145,161,201,170,178,81,205,196,7,88,145,22,62,117,54,88,86,239,51,130,15,48,162,76,44,181,126,229,131,96,159,161,252,0,67,242,129,58,107,110,134,57,57,3,162,151,199,252,81,133,157,17,153,132,70,38,118,173,162,178,74,235,205,21,59,86,50,144,154,21,131,252,86,145,52,137,31,91,208,125,173,189,139,73,234,223,79,37,245,21,46,74,125,216,13,60,63,0,120,190,11,152,156,26,236,134,62,192,125,233,108,23,52,57,222,217,13,29,29,0,29,237,130,166,71,50,187,177,179,3,176,179,26,108,229,7,5,98,222,226,129,207,177,135,17,77,52,250,228,186,244,242,128,188,211,20,47,179,59,132,250,103,139,11,4,171,248,77,135,200,115,15,224,111,144,100,186,90,121,164,251,126,1,194,23,164,21,164,48,190,23,75,253,161,72,9,71,241,180,242,91,186,228,199,45,247,211,168,234,192,106,63,45,219,197,145,80,5,187,179,141,189,131,214,61,240,197,73,17,253,9,143,116,224,224,74,123,26,210,196,10,61,221,48,41,199,43,86,147,190,110,53,136,35,17,171,201,150,162,219,237,236,48,196,114,216,123,11,145,203,121,197,40,52,215,72,51,77,0,178,29,22,217,176,152,98,163,37,48,69,35,93,80,81,33,221,200,80,2,244,172,206,160,75,57,195,150,160,69,159,152,252,230,131,119,37,146,150,232,223,52,88,61,86,122,41,19,160,186,235,131,41,157,132,37,133,205,4,50,219,255,248,116,218,104,127,110,26,134,197,14,230,200,63,231,191,67,196,6,105,89,42,0,0 };
