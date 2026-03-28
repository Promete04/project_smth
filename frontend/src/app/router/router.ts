import { Component, input } from '@angular/core';
import { CdkDrag } from '@angular/cdk/drag-drop';
import { MapElement } from '../interfaces/MapElement';

@Component({
  selector: 'app-router',
  imports: [CdkDrag],
  templateUrl: './router.html',
  styleUrl: './router.css',
})
export class Router extends MapElement {
  subnet = input<string>();
  ip = input<string>();
}
