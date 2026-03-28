import { Component, input } from '@angular/core';

export interface IService {
  port: number;
  name?: string;
  status?: string;
}

@Component({
  selector: 'app-service',
  imports: [],
  templateUrl: './service.html',
  styleUrl: './service.css',
})
export class Service {
  port = input<string>();
  name = input<string>();
  status = input<string>();
}
