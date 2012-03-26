var NAVTREE =
[
  [ "BoostHttpServer", "index.html", [
    [ "Boost C++ HTTP Server", "index.html", null ],
    [ "Related Pages", "pages.html", [
      [ "Todo List", "todo.html", null ]
    ] ],
    [ "Class List", "annotated.html", [
      [ "http::server::connection", "classhttp_1_1server_1_1connection.html", null ],
      [ "http::server::connection_manager", "classhttp_1_1server_1_1connection__manager.html", null ],
      [ "http::server::header", "structhttp_1_1server_1_1header.html", null ],
      [ "http::server::mime_types::mapping", "structhttp_1_1server_1_1mime__types_1_1mapping.html", null ],
      [ "http::server::reply", "structhttp_1_1server_1_1reply.html", null ],
      [ "http::server::request", "structhttp_1_1server_1_1request.html", null ],
      [ "http::server::request_handler", "classhttp_1_1server_1_1request__handler.html", null ],
      [ "http::server::request_parser", "classhttp_1_1server_1_1request__parser.html", null ],
      [ "http::server::server", "classhttp_1_1server_1_1server.html", null ]
    ] ],
    [ "Class Index", "classes.html", null ],
    [ "Class Members", "functions.html", null ],
    [ "Namespace List", "namespaces.html", [
      [ "http", "namespacehttp.html", null ],
      [ "http::server", "namespacehttp_1_1server.html", null ],
      [ "http::server::mime_types", "namespacehttp_1_1server_1_1mime__types.html", null ],
      [ "http::server::misc_strings", "namespacehttp_1_1server_1_1misc__strings.html", null ],
      [ "http::server::status_strings", "namespacehttp_1_1server_1_1status__strings.html", null ],
      [ "http::server::stock_replies", "namespacehttp_1_1server_1_1stock__replies.html", null ]
    ] ],
    [ "Namespace Members", "namespacemembers.html", null ],
    [ "File List", "files.html", [
      [ "src/connection.cpp", "connection_8cpp.html", null ],
      [ "src/connection.hpp", "connection_8hpp.html", null ],
      [ "src/connection_manager.cpp", "connection__manager_8cpp.html", null ],
      [ "src/connection_manager.hpp", "connection__manager_8hpp.html", null ],
      [ "src/header.hpp", "header_8hpp.html", null ],
      [ "src/mime_types.cpp", "mime__types_8cpp.html", null ],
      [ "src/mime_types.hpp", "mime__types_8hpp.html", null ],
      [ "src/posix_main.cpp", "posix__main_8cpp.html", null ],
      [ "src/reply.cpp", "reply_8cpp.html", null ],
      [ "src/reply.hpp", "reply_8hpp.html", null ],
      [ "src/request.hpp", "request_8hpp.html", null ],
      [ "src/request_handler.cpp", "request__handler_8cpp.html", null ],
      [ "src/request_handler.hpp", "request__handler_8hpp.html", null ],
      [ "src/request_parser.cpp", "request__parser_8cpp.html", null ],
      [ "src/request_parser.hpp", "request__parser_8hpp.html", null ],
      [ "src/server.cpp", "server_8cpp.html", null ],
      [ "src/server.hpp", "server_8hpp.html", null ],
      [ "src/win_main.cpp", "win__main_8cpp.html", null ]
    ] ],
    [ "File Members", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

