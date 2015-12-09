/**
 * Copyright 2014 IBM Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

// If you use this as a template, update the copyright with your own name.

// Sample Node-RED node file


module.exports = function(RED) {
    "use strict";
    // require any external libraries we may need....
   
	var PF = require('pathfinding');
    // The main node definition - most things happen in here
    function PathfindingNode(n) {
        // Create a RED node
        RED.nodes.createNode(this,n);

        // Store local copies of the node configuration (as defined in the .html)
        this.topic = n.topic;

        // copy "this" object in case we need it in context of callbacks of other functions.
        var node = this;

        // Do whatever you need to do in here - declare callbacks etc
        // Note: this sample doesn't do anything much - it will only send
        // this message once at startup...
        // Look at other real nodes for some better ideas of what to do....
      
        // send out the message to the rest of the workspace.
        // ... this message will get sent at startup so you may not see it in a debug node.
   
			
        // respond to inputs....
        this.on('input', function (msg) {
			
		var words = msg.payload.split(" ");
		var n=5;
		var m=5;
		var matrix = 
						[[1, 0, 0, 0, 0],
                         [0, 1, 0, 1, 0],
                         [0, 0, 0, 1, 0],
                         [0, 1, 1, 0, 0],
                         [0, 1, 0, 0, 1],
                         ]

	var cel=[2,4];
	var kezd=[0,4];
		if(words[0]=="get"){
		msg.payload=n+","+m+"\n";
		msg.payload+=matrix;
		msg.payload+="\n"+kezd+"\n"+cel+"\n";
		node.warn("I saw a payload: "+msg.payload);
        // in this example just send it straight on... should process it here really
        var signalmsg = { payload:"1" };
		node.send([msg,signalmsg,null]);
		//return [msg,signalmsg,null];
		}
		else if(words[0]=="help"){
		var grid = new PF.Grid( matrix);
		// grid = new PF.Grid(matrix);
		//var finder = new PF.AStarFinder
		var finder = new PF.AStarFinder({
		diagonalMovement: PF.DiagonalMovement.Never
		});

		var x=words[1];
		var y=words[2];
		var path = finder.findPath(words[1], words[2], cel[0],cel[1], grid);
		 
		
		msg.payload="";
		for (var i = 1; i < path.length; i++) {
				 if (path[i][0]==(x+1)) {/*msg.payload+="Jobbra"+",";*/msg.payload+="2"+",";x++;}
			else if (path[i][0]==(x-1)) {/*msg.payload+="Balra"+",";*/msg.payload+="4"+",";x--;}
			else if (path[i][1]==(y+1)) {/*msg.payload+="Le"+",";*/msg.payload+="3"+",";y++;}
			else if (path[i][1]==(y-1)) {/*msg.payload+="Fel"+",";*/msg.payload+="1"+",";y--;}
			else msg.payload+="error ";
		}
		//msg.payload=path;
		var signalmsg = { payload:"4" };
		   node.warn("word contains: "+words[0]+"\n"+words[1]+"\n"+words[2]);
		   node.warn("I saw a payload: "+path);
            // in this example just send it straight on... should process it here really
            node.send([null,signalmsg,msg]);
			//return [null,signalmsg,msg];
		}
                 });

        this.on("close", function() {
            // Called when the node is shutdown - eg on redeploy.
            // Allows ports to be closed, connections dropped etc.
            // eg: node.client.disconnect();
        });
    }

    // Register the node by name. This must be called before overriding any of the
    // Node functions.
    RED.nodes.registerType("Pathfinding",PathfindingNode);

}
