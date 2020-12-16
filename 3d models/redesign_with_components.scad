$fa=0.5; // default minimum facet angle is now 0.5
$fs=0.5; // default minimum facet size is now 0.5 mm

instr();
module instr() {
difference() {
difference() {
difference() {
difference() {
difference(){
color([0.4,0,0])
difference() {
hull() {
color([0.3,0,0])cube([50,10,2], center = true);
translate([17,7,-1])cylinder(h = 2, r = 8);
}

translate([-11,50,-2])cylinder(h = 4, r = 40);
}



scale([0.9,0.7,2])
translate([-2,-0.5,1])color([0,0,0])cube([50,11,1.2], center= true);

color([0.3,0,0]) hull() {
translate([17,7,1])cylinder(h = 0.5, r = 7);
translate([0,0,1])cube([10,10,2]);
}

translate([32,3,-1.5])cylinder(h = 4, r = 10);


}

translate([29,3,-8])sphere(r = 11);

}


}

rotate([0,0,100])
resize([20,50,10])
translate([14,4,-9])sphere( r= 10);
}

rotate([2,5,95])
resize([20,50,10])
translate([-7,-1,-11])sphere( r= 10);
}



color([0.3,0,0])
rotate([0,0,90])
translate([4,0,1])
right_triangle(6,24,0.1,0.1);

module right_triangle(side1,side2,corner_radius,triangle_height){
  translate([corner_radius,corner_radius,0]){  
    hull(){  
    cylinder(r=corner_radius,h=triangle_height);
      translate([side1 - corner_radius * 2,0,0])cylinder(r=corner_radius,h=triangle_height);
          translate([0,side2 - corner_radius * 2,0])cylinder(r=corner_radius,h=triangle_height);  
    }
  }
    
}

rotate([0,90,0])
translate([-1.2,4.2,-23])cylinder(h = 23, r = 0.1);

rotate([0,90,0])
translate([-1.2,6,-17])cylinder(h = 17, r = 0.1);

rotate([0,90,0])
translate([-1.2,7.8,-9])cylinder(h = 9, r = 0.1);

// KNOBS AND COMPONENTS

translate([2,-1,0])
union () {
color([1,1,1])
translate([10,12,1])cylinder(h = 0.75, r = 0.4);
color([0,0,0])
translate([10,12,0])cylinder(h = 1.7, r = 0.7);

color([1,1,1])
translate([13,12.7,0])cylinder(h = 1.75, r = 0.4);
color([0,0,0])
translate([13,12.7,0])cylinder(h = 1.7, r = 0.7);

color([1,1,1])
translate([12,9,0])cylinder(h = 1.75, r = 0.4);
color([0,0,0])
translate([12,9,0])cylinder(h = 1.7, r = 0.7);

color([1,1,1])
translate([15,9.5,0])cylinder(h = 1.75, r = 0.4);
color([0,0,0])
translate([15,9.5,0])cylinder(h = 1.7, r = 0.7);
    
}

}




*projection(cut = true) instr();