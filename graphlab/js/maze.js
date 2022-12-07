/**
 * This is used to render maze.
 */

// extern graph: Graph from graph.js

const CANVAS_SIZE = 480;    // 480 * 480

var canvas = document.getElementById("maze");
canvas.style.width = 480 + "px";
canvas.style.height = 480 + "px";

class Renderer {
    constructor() {
        this.device = canvas.getContext("2d");
        this.px = 0;    // padding x
        this.py = 0;    // padding y
        this.x = 0;     // origin x
        this.y = 0;     // origin y
        this.unit = 0;  // unit block size
        this.width = 0;
        this.height = 0;
        this.graph = null;
    }

    init(g) {
        this.graph = g;
        this.width = g.width;
        this.height = g.height;

        var u = Math.max(this.width, this.height);
        this.unit = Math.floor(CANVAS_SIZE / u);

        var w = this.width * this.unit;
        var h = this.height * this.unit;
        this.px = (CANVAS_SIZE - w) / 2;
        this.py = (CANVAS_SIZE - h) / 2;
        this.x = this.px + this.unit / 2;
        this.y = this.py + this.unit / 2;
    }

    drawBackground() {
        this.device.save();

        this.device.clearRect(0, 0, CANVAS_SIZE, CANVAS_SIZE);
        this.device.fillStyle = wallColor;
        this.device.fillRect(this.px - this.unit / 4,this.py - this.unit / 4, this.width * this.unit + this.unit / 2, this.height * this.unit + this.unit / 2);

        this.device.restore();
    }

    drawEdge(u, v, c) {
        var x1 = this.x + Math.floor(((u - 1) % this.width)) * this.unit;
        var y1 = this.y + Math.floor(((u - 1) / this.width)) * this.unit;
        var x2 = this.x + Math.floor(((v - 1) % this.width)) * this.unit;
        var y2 = this.y + Math.floor(((v - 1) / this.width)) * this.unit;

        var left = Math.floor(Math.min(x1, x2)) - this.unit / 4;
        var top = Math.floor(Math.min(y1, y2)) - this.unit / 4;
        var right = Math.floor(Math.max(x1, x2)) + this.unit / 4;
        var bottom = Math.floor(Math.max(y1, y2)) + this.unit / 4;

        this.device.save();

        this.device.fillStyle = c;
        this.device.fillRect(left, top, right - left, bottom - top);

        this.device.restore();
    }

    draw() {
        var list = this.graph.edgeList;
        this.drawBackground();

        for (var i = 0; i < list.length; i++) {
            switch (list[i].tag) {
                case EDGE_NONE:
                    break;
                case EDGE_FLOOR:
                    this.drawEdge(list[i].u, list[i].v, floorColor);
                    break;
                case EDGE_SRC:
                    this.drawEdge(list[i].u, list[i].v, srcColor);
                    break;
                case EDGE_DST:
                    this.drawEdge(list[i].u, list[i].v, destColor);
                    break;
                default:
                    break;
            }
        }

        for (var i = 0; i < list.length; i++) {
            if (list[i].tag == EDGE_DEAD) {
                this.drawEdge(list[i].u, list[i].v, deadColor);
            }
        }
        
        for (var i = 0; i < list.length; i++) {
            if (list[i].tag == EDGE_PATH) {
                this.drawEdge(list[i].u, list[i].v, pathColor);
            }
        }

        this.drawEdge(1, 1, srcColor);
        this.drawEdge(this.graph.size, this.graph.size, destColor);
    }
}

var renderer = new Renderer();