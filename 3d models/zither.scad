$fa=0.5; // default minimum facet angle is now 0.5
$fs=0.5; // default minimum facet size is now 0.5 mm



scale([1,1,1]) {
difference () {
    
scale([1.1,1.1,1.1]) {
    

union () { 
color([0.3,0,0])
difference () { 
hull() {
    
    
//draw();

union () {
    cube([50,15,2], center = true);
    translate([10,5,-1])
    cylinder( h = 2, r = 16);
    //translate([8,5,-1])
    //cylinder( h = 2, r = 15);

}

    translate([-15,-5,-1])
    color([1,0,0])cylinder( h = 2, r = 7);


}

translate([-31,-17,-2])
color([1,0,0])cylinder( h = 4, r = 15);
//translate([-18,41,-1])
//color([1,0,0])cylinder( h = 4, r = 30);

translate([44,0,-2])
color([1,0,0])cylinder( h = 20, r = 25);

}

}
}    
    
union () { 
color([0.3,0,0])
difference () { 
hull() {
    

    
//draw();

union () {
    cube([50,15,3], center = true);
    translate([10,5,-1])
    cylinder( h = 2, r = 16);
    //translate([8,5,-1])
    //cylinder( h = 2, r = 15);

}

    translate([-15,-5,-1])
    color([1,0,0])cylinder( h = 2, r = 7);


}

translate([-31,-17,-1])
color([1,0,0])cylinder( h = 3, r = 15);
//translate([-18,41,-1])
//color([1,0,0])cylinder( h = 4, r = 30);

translate([44,0,-1])
color([1,0,0])cylinder( h = 3, r = 25);

}

}

 



}


union() {
color([0,0,0])
translate ([-27,-3.5,0])
cube([47.5 ,11,0.5]);

color([0,0,0])
translate ([-20,-10,0])
cube([40 ,11,0.5]);

color([0,0,0])
translate ([-20,-10,0])
cube([40 ,11,0.5]);

color([0,0,0])
translate ([-20,-10,0])
cube([40 ,7,0.5]);

color([0,0,0])
translate ([-20,-10.3,0])
cube([40 ,3,0.5]);

color([0,0,0])
translate ([-17,-11.6,0])
cube([32 ,2,0.5]);


translate([-14,-6,0])
color([0,0,0])cylinder( h = 0.5, r = 7);

translate([-8,-5,0])
color([0,0,0])cylinder( h = 0.5, r = 7.5);

translate([-22,-2,0])
color([0,0,0])cylinder( h = 0.5, r = 4);

translate([18,-7,0])
color([0,0,0])cylinder( h = 0.5, r = 3);
}

    union() {
 
    translate([-25,9,0])
    rotate([0,90,0]) cylinder(h = 47 ,r = 0.2);

    translate([-15,12,0])
    rotate([0,90,0]) cylinder(h = 37 ,r = 0.2);

    translate([-11,15,0])
    rotate([0,90,0]) cylinder(h = 34 ,r = 0.2);
    }
     
    union() {
    color([0.3,0,0])
    translate([0,7.5,0]) cube([21,12,0.5]);
    color([0.3,0,0])
    translate([17.5,14,0]) cylinder(h = 0.5 , r = 6);
    color([0.3,0,0])
    translate([10,16,0]) cylinder(h = 0.5 , r = 7.5);
        
    }

}



