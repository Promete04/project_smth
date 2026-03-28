import { ComponentFixture, TestBed } from '@angular/core/testing';

import { Router } from './router';

describe('Router', () => {
  let component: Router;
  let fixture: ComponentFixture<Router>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [Router],
    }).compileComponents();

    fixture = TestBed.createComponent(Router);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
