import { Component, input } from '@angular/core';
import { CdkDrag } from '@angular/cdk/drag-drop';
@Component({
  selector: 'app-router',
  imports: [CdkDrag],
  templateUrl: './router.html',
  styleUrl: './router.css',
})
export class Router {
  subnet = input<string>();
}
